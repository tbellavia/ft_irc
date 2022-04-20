/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdFactory.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbellavi <bbellavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:22:35 by bbellavi          #+#    #+#             */
/*   Updated: 2022/04/20 14:51:53 by bbellavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDFACTORY_HPP
#define CMDFACTORY_HPP

# include <map>
# include "ICmdFactory.hpp"

namespace IRC
{
	class CmdFactory : public ICmdFactory {
		typedef ACmd *(*CmdFactory::*callback_t)(CmdCtx&, std::string const&);

		std::map<std::string, callback_t> m_callbacks;
	public:
		CmdFactory();

		ACmd *create_cmd(CmdCtx &ctx, std::string const &request);
	};
}


#endif
