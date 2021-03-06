/*
 * Copyright (c) 2012-2016 soymuchacho <guqi_282@126.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * > LIBSHARED  VERSION 		:		0.0.1 
 * > File Name					:		TcpSocket.cpp
 * > Author						:		soymuchacho
 * > Created Time				:		2015-10
 * > brief						:		Tcp 连接 
 *
 * */

#include <network/TcpSocket.h>
#include <include/Event_Interface.h>
#include <common/Log.h>
#include <common/Mutex.h>

namespace Shared
{

#define SD_RECEIVE	0x00
#define SD_SEND		0x01
#define SD_BOTH		0x02

/*
 *	@ qi_gu 
 *	@ 2015.11.4
 *
 *	知识点：
 *
 *	linux 下写socket的程序的时候，如果尝试send到一个disconnect socket上，就会让底层抛出一个SIGPIPE信号
 *	client端通过pipe发送信息到server端后，就关闭client端，这时server端返回信息给client端时就产生Broken pipe
 *	信号了。对于产生信号，我们可以在产生信号前利用方法signal（int signum，sighandler_t handler）设置信号的
 *	处理。如果没有调用此方法，系统就会调用默认处理方式：中止程序，显示提示信息（就是我们经常遇到的问题）。我们
 *	可以调用系统的处理方法，也可以自定义处理方法。
 *
 *	对一个已经收到FIN包的socket调用read方法，如果接收缓冲已空，则返回0,
 *	这就是常说的表示连接关闭，但第一次对其调用write方法时，如果发送缓冲
 *	没问题，会返回正确写入（发送），但发送的报文会导致对端发送RST报文，因为
 *	对端的socket已经调用了close，完全关闭，即不发送，也不接收数据。所以，第
 *	二次调用write方法（假设在RST之后），会生成SIGPIPE信号，导致进程退出，为了
 *	避免进程退出，可以捕获SIGPIPE信号，或者忽略它。
 *
 *	给它设置SIG_IGN信号处理：
 *	signal(SIGPIPE,SIG_IGN);
 *	这样第二次调用write方法时，会返回-1，同时errno置为SIGPIPE,程序就知对端已经关闭。
 *
 */



TcpSocket::TcpSocket(int fd,const struct sockaddr_in * peer)
{
	SetFd(fd);	

	readBuffer = MM_NEW<Buffer>();
	writeBuffer = MM_NEW<Buffer>();
	
	memcpy(&m_peer,peer,sizeof(sockaddr));
	long arg = 1;
	ioctl(fd,FIONBIO,&arg);

	m_writeLock = 0;
	m_connected = true;
	m_bIsListen = false;
}

TcpSocket::~TcpSocket()
{
	MM_DELETE(readBuffer);
	MM_DELETE(writeBuffer);
	m_writeLock = 0;
}

bool TcpSocket::OnRead()
{
	int total = 0;
	MutexLockGuard lock(&m_readMutex);
	while(true)
	{
		int space = readBuffer->GetWriteSpace();
		if(space == 0)
		{
			break;
		}	
		int bytes = recv(m_uFd,(char *)readBuffer->GetWriteOffSet(),space,0);
		if(bytes == 0 )
		{
			LOGDEBUG("libshared","read 0,the peer has been closed");
			return false;
		}
		else if(bytes < 0)
		{
			if(errno != EAGAIN)
			{
				return false;
			}
		}
		else
		{
			total += bytes;
			readBuffer->IncrementWritten(bytes);	
			if(bytes == space)
			{
				continue;
			}

			if(bytes < space)
				break;
		}
	}
	
	if(total > 0)
	{
		if(OnRecvData() == false)
		{
			return false;
		}

		if(readBuffer->GetReadSize() == 0)
		{
			readBuffer->clear_all_data();
		}
		
	}
	return true;
}

bool TcpSocket::OnRecvData()
{
	while(readBuffer->GetReadSize() > 0)
	{
		if(Dispatch() == false)
			return false;
	}
	return true;
}

void TcpSocket::OnError()
{
	Disconnect();
}

bool TcpSocket::OnWrite()
{
	LockWriteBuffer();
	
	unsigned long space = writeBuffer->GetReadSize();
	if(space == 0)
	{
		UnLockWriteBuffer();
		return true;
	}
	
	unsigned long total = 0;
	while(true)
	{
		int bytes = writeBuffer->GetReadSpace();	
		if(bytes <= 0)
		{
			break;
		}
		int size = send(m_uFd,writeBuffer->GetReadOffSet(),bytes,0);
		if(size < 0 )
		{
			if(errno != EAGAIN)
			{
				UnLockWriteBuffer();
				return false;
			}
			else
				break;
		}
		else
		{
			total += size;
			writeBuffer->IncrementRead(size);
			if(size < bytes)
				break;
		}
	}

	if(total == space)
	{
		writeBuffer->clear_all_data();
	}
	UnLockWriteBuffer();
	return true;
}

int TcpSocket::Write(void * data,int size)
{
	if(! m_connected)
		return -1;
	LockWriteBuffer();
	writeBuffer->Write((char *)data,size);
	if(!m_writeLock)
	{
		++m_writeLock;
		basesocket_sptr s;
		sockengine_sptr sptr;
		if(GetSocketEngine(sptr))
		{
			if(sptr->GetSocket(GetFd(),GetCtime(),s))
				sptr->WantWrite(s);
		}
	}
	UnLockWriteBuffer();
}

void TcpSocket::Finalize(basesocket_sptr s)
{
	if(s)
	{
		sockengine_sptr sptr;
		if(GetSocketEngine(sptr))
		{
			sptr->AddSocket(s);
			m_connected = true;
			OnConnect();
		}
	}
	else
	{
		// 出现怎么办？ 自宫吧
		Disconnect();
	}
}

void TcpSocket::OnConnect()
{

}

void TcpSocket::OnDisConnect()
{

}

void TcpSocket::Disconnect()
{
	if(!m_connected) return;
	m_connected = false;
	this->OnDisConnect();
	// 将缓冲区中没有发送的数据发送完毕
	this->OnWrite();	
	// 2015.10.22 guqi
	// 关闭m_uFd的时候也能触发
	// epoll_ctl del操作，所以将
	// RemoveSocket提前
	//se->RemoveSocket(this);
	shutdown(m_uFd,SD_BOTH);
	close(m_uFd);
	Delete();
	LOGDEBUG("libshared","tcp disconnect ...");
}

void TcpSocket::Delete()
{
	basesocket_sptr s;
	sockengine_sptr sptr;
	if(GetSocketEngine(sptr))
	{
		if(sptr->GetSocket(GetFd(),GetCtime(),s))
			sptr->DeleteSocket(s);//delete this;
	}
}

bool TcpSocket::Writeable()
{
	if(writeBuffer == NULL)
	{
		return false;
	}
	if(writeBuffer->GetReadSize() > 0)
		return true;
	else
		return false;
}

}
