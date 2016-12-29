/*
    Copyright (C) 2000-2007 Paul Davis

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

*/

#include <cmath>
#include <errno.h>

#include "fix_carbon.h"

#include "pbd/gstdio_compat.h"

#include <gtkmm/settings.h>

#include "gtkmm2ext/gtk_ui.h"
#include "gtkmm2ext/utils.h"

#include "pbd/compose.h"

#include "ardour/profile.h"

#include "canvas/wave_view.h"

#include "ardour_button.h"
#include "ardour_dialog.h"
#include "theme_manager.h"
#include "ui_config.h"
#include "utils.h"

#include "pbd/i18n.h"

using namespace std;
using namespace Gtk;
using namespace PBD;
using namespace ARDOUR;
using namespace ARDOUR_UI_UTILS;

ThemeManager::ThemeManager()
{
	BoolOption* bo;

	bo = new BoolOption (
			"flat-buttons",
			_("Draw \"flat\" buttons"),
			sigc::mem_fun (UIConfiguration::instance(), &UIConfiguration::get_flat_buttons),
			sigc::mem_fun (UIConfiguration::instance(), &UIConfiguration::set_flat_buttons)
			);
	bo->add_to_page (this);
	bo->set_state_from_config ();

	vector<string> icon_sets = ::get_icon_sets ();
	if (icon_sets.size() > 1) {
		ComboOption<std::string>* io = new ComboOption<std::string> (
				"icon-set", _("Icon Set"),
				sigc::mem_fun (UIConfiguration::instance(), &UIConfiguration::get_icon_set),
				sigc::mem_fun (UIConfiguration::instance(), &UIConfiguration::set_icon_set)
				);
		for (vector<string>::const_iterator i = icon_sets.begin (); i != icon_sets.end (); ++i) {
			io->add (*i, *i);
		}
		io->add_to_page (this);
		io->set_state_from_config ();
	}

	HSliderOption *hs = new HSliderOption(
			"timeline-item-gradient-depth",
			_("Waveforms color gradient depth"),
			sigc::mem_fun (UIConfiguration::instance(), &UIConfiguration::get_waveform_gradient_depth),
			sigc::mem_fun (UIConfiguration::instance(), &UIConfiguration::set_waveform_gradient_depth),
			0, 1.0, 0.05
			);
	hs->scale().set_update_policy (Gtk::UPDATE_DELAYED);
	hs->add_to_page (this);
	hs->set_state_from_config ();

	hs = new HSliderOption(
			"timeline-item-gradient-depth",
			_("Timeline item gradient depth"),
			sigc::mem_fun (UIConfiguration::instance(), &UIConfiguration::get_timeline_item_gradient_depth),
			sigc::mem_fun (UIConfiguration::instance(), &UIConfiguration::set_timeline_item_gradient_depth),
			0, 1.0, 0.05
			);
	hs->scale().set_update_policy (Gtk::UPDATE_DELAYED);
	hs->add_to_page (this);
	hs->set_state_from_config ();
}

void
ThemeManager::set_state_from_config ()
{
}
