/**************************************************************************
**
** This file is part of Doxygen plugin for Qt Creator
**
** Copyright (c) 2009 Kevin Tanguy (kofee@kofee.org).
** Copyright (c) 2015 Fabien Poussin (fabien.poussin@gmail.com).
**
** This plugin is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as
** published by the Free Software Foundation, either version 2.1
** of the License, or (at your option) any later version.
**
** This plugin is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with Doxygen Plugin. If not, see <http://www.gnu.org/licenses/>.
**/

#ifndef DOXYGENSETTINGSWIDGET_H
#define DOXYGENSETTINGSWIDGET_H

#include <coreplugin/dialogs/ioptionspage.h>
#include <utils/pathchooser.h>
#include "doxygensettingsstruct.h"

namespace Ui {
    class DoxygenSettingsWidget;
}

namespace DoxyPlugin {
namespace Internal {

class DoxygenSettings;

class DoxygenSettingsWidget : public Core::IOptionsPageWidget
{
    Q_OBJECT
public:
    explicit DoxygenSettingsWidget(DoxygenSettings *settings);
    ~DoxygenSettingsWidget() override;

    void apply() override;
    void cancel() override;
    bool isDirty() const override;

    DoxygenSettingsStruct settings() const;
    void setSettings(const DoxygenSettingsStruct &);

protected:
    void changeEvent(QEvent *e) override;

private:
    Ui::DoxygenSettingsWidget *ui;
    DoxygenSettings *m_settings;

    void updateFileCommentPreview();

private slots:
    void updateCustomWidgetPart(int index);
    void on_fileComments_clicked(bool checked);
    void on_fcommentChooser_currentIndexChanged(int index);
};

} // namespace Internal
} // namespace DoxyPlugin

#endif // DOXYGENSETTINGSWIDGET_H
