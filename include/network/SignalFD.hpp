/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SignalFD.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperson- <lperson-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 18:16:57 by lperson-          #+#    #+#             */
/*   Updated: 2022/06/14 19:42:38 by lperson-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_FD_HPP

# define SIGNAL_FD_HPP

# include "IFileObj.hpp"
# include <signal.h>
# include <vector>

class SignalFD : public IFileObj
{
public:
	SignalFD();
	SignalFD(std::vector<int> signals);
	SignalFD(sigset_t const &sigmask);
	SignalFD(SignalFD const &copy);
	~SignalFD();

	int fd() const;

	void set_mask(sigset_t const &sigmask);
	void close();

private:
	sigset_t	m_sigmask;
	int			m_filedesc;
};

#endif
