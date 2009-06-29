## Copyright (C) 2009 Onno Kortmann <onno@gmx.net>
##  
## This program is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 2 of the License, or
## (at your option) any later version.
##  
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##  
## You should have received a copy of the GNU General Public License
## along with this program; if not, write to the Free Software
## Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
##  

#for $Letter in $io_ports
#set $letter=$Letter.lower    
#set $port=$io_ports[$Letter]
##    
#if ("PIN"+$Letter) in $io
    port$letter=new HWPort(this, "$Letter");
#else
    // output-only port
    port$letter=new HWPort(this, "$Letter", 0xff);
#endif
##    
#if ("PORT"+$Letter) in $io
    rw[$io["PORT"+$Letter].addr]=new RWPort(this, port$letter);
#endif
##    
## some ports are output only (e.g. mega103/portc)
## some other ports are input only (e.g. mega103/portf)
#if ("PIN"+$Letter) in $io
    rw[$io["PIN"+$Letter].addr]=new RWPin (this, port$letter);
    #if ("PORT"+$Letter) in $io
    rw[$io["DDR"+$Letter].addr]=new RWDdr (this, port$letter);
    #else
    // ^^ input-only port
    #endif
  #endif

#endfor
