/* JobHoldUntil.java -- 
   Copyright (C) 2004 Free Software Foundation, Inc.

This file is part of GNU Classpath.

GNU Classpath is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

GNU Classpath is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU Classpath; see the file COPYING.  If not, write to the
Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
02110-1301 USA.

Linking this library statically or dynamically with other modules is
making a combined work based on this library.  Thus, the terms and
conditions of the GNU General Public License cover the whole
combination.

As a special exception, the copyright holders of this library give you
permission to link this library with independent modules to produce an
executable, regardless of the license terms of these independent
modules, and to copy and distribute the resulting executable under
terms of your choice, provided that you also meet, for each linked
independent module, the terms and conditions of the license of that
module.  An independent module is a module which is not derived from
or based on this library.  If you modify this library, you may extend
this exception to your version of the library, but you are not
obligated to do so.  If you do not wish to do so, delete this
exception statement from your version. */


package javax.print.attribute.standard;

import java.util.Date;

import javax.print.attribute.DateTimeSyntax;
import javax.print.attribute.PrintJobAttribute;
import javax.print.attribute.PrintRequestAttribute;

/**
 * @author Michael Koch (konqueror@gmx.de)
 */
public final class JobHoldUntil extends DateTimeSyntax
  implements PrintJobAttribute, PrintRequestAttribute
{
  private static final long serialVersionUID = -1664471048860415024L;

  /**
   * Creates a <code>JobHoldUntil</code> object.
   *
   * @param value the date to hold the job until
   *
   * @exception NullPointerException if value is null
   */
  public JobHoldUntil(Date value)
  {
    super(value);
  }

  /**
   * Tests of obj is equal to this object.
   *
   * @param obj the object to test
   *
   * @return true if both objects are equal, false otherwise.
   */
  public boolean equals(Object obj)
  {
    if(! (obj instanceof JobHoldUntil))
      return false;

    return super.equals(obj);
  }

  /**
   * Returns category of this class.
   *
   * @return the class <code>JobHoldUntil</code> itself
   */
  public Class getCategory()
  {
    return JobHoldUntil.class;
  }

  /**
   * Returns name of this class.
   *
   * @return the string "job-hold-until"
   */
  public String getName()
  {
    return "job-hold-until";
  }
}