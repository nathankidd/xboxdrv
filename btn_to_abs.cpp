/*  $Id$
**   __      __ __             ___        __   __ __   __
**  /  \    /  \__| ____    __| _/_______/  |_|__|  | |  |   ____
**  \   \/\/   /  |/    \  / __ |/  ___/\   __\  |  | |  | _/ __ \
**   \        /|  |   |  \/ /_/ |\___ \  |  | |  |  |_|  |_\  ___/
**    \__/\  / |__|___|  /\____ /____  > |__| |__|____/____/\___  >
**         \/          \/      \/    \/                         \/
**  Copyright (C) 2007 Ingo Ruhnke <grumbel@gmx.de>
**
**  This program is free software; you can redistribute it and/or
**  modify it under the terms of the GNU General Public License
**  as published by the Free Software Foundation; either version 2
**  of the License, or (at your option) any later version.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
** 
**  You should have received a copy of the GNU General Public License
**  along with this program; if not, write to the Free Software
**  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
**  02111-1307, USA.
*/

#include <boost/bind.hpp>
#include "btn_to_abs.hpp"

BtnToAbs::BtnToAbs()
  : target_value(0)
{
  btn_port_in.push_back(new BtnPortIn("BtnToAbs-Out-0",
                                      boost::bind(&BtnToAbs::on_btn, this, _1)));
  btn_port_in.push_back(new BtnPortIn("BtnToAbs-Out-1",
                                      boost::bind(&BtnToAbs::on_btn, this, _1)));

  abs_port_out.push_back(new AbsPortOut("BtnToAbs-In", -32767, 32767));
}

void
BtnToAbs::update(float delta)
{
  // make this configurable
  float relax = 0.05f;
  abs_port_out[0]->set_state(int(abs_port_out[0]->get_state() + 
                                 relax * (target_value - abs_port_out[0]->get_state())));
}

void
BtnToAbs::on_btn(BtnPortOut* port)
{
  if (btn_port_in[0]->out_port->get_state() &&
      !btn_port_in[1]->out_port->get_state())
    {
      target_value = abs_port_out[0]->min_value;
    } 
  else if (!btn_port_in[0]->out_port->get_state() &&
           btn_port_in[1]->out_port->get_state())
    {
      target_value = abs_port_out[0]->max_value;
    }
  else
    {
      target_value = 0;
    }
}

/* EOF */
