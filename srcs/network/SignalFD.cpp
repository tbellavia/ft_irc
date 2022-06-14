/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SignalFD.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 18:23:34 by lperson-          #+#    #+#             */
/*   Updated: 2022/06/14 19:51:12 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SignalFD.hpp"
#include <unistd.h>
#include <sys/signalfd.h>

SignalFD::SignalFD():
		m_sigmask(),
		m_filedesc(-1)
{
}

SignalFD::SignalFD(std::vector<int> signals):
		m_filedesc(-1)
{
	sigset_t sigmask;
	sigemptyset(&sigmask);
	for (std::size_t i = 0; i < signals.size(); ++i)
		sigaddset(&sigmask, signals[i]);
	this->set_mask(sigmask);
}

SignalFD::SignalFD(sigset_t const &sigmask):
		m_sigmask(sigmask),
		m_filedesc(-1)
{
	this->set_mask(sigmask);
	m_filedesc = signalfd(-1, &m_sigmask, 0);
}

SignalFD::SignalFD(SignalFD const &copy):
		m_sigmask(copy.m_sigmask),
		m_filedesc(copy.m_filedesc)
{
}

SignalFD::~SignalFD()
{
}

int SignalFD::fd() const
{
	return m_filedesc;
}

void SignalFD::set_mask(sigset_t const &sigmask)
{
	if (m_filedesc >= 0)
		this->close();

	m_sigmask = sigmask;
	sigset_t oldsig;
	sigprocmask(SIG_BLOCK, &m_sigmask, &oldsig);
	for (std::size_t i = 0; i < 32; ++i)
	{
		if (sigismember(&oldsig, i) == 1)
			sigdelset(&oldsig, i);
	}
	sigprocmask(SIG_UNBLOCK, &oldsig, NULL);
	m_filedesc = signalfd(-1, &m_sigmask, 0);
}

void SignalFD::close()
{
	::close(m_filedesc);
	m_filedesc = -1;
}
