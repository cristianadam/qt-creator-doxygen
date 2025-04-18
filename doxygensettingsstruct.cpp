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

#include "doxygensettingsstruct.h"

#include <utils/qtcsettings.h>

#include <QStringList>
#include <QTextStream>
using namespace DoxyPlugin;
using namespace DoxyPlugin::Internal;

static const char* groupC = "Doxygen";
static const char* commandKeyC = "Command";
static const char* doxyfilePathKeyC = "DoxyConfigFile";
static const char* wizardcommandKeyC = "Wizard";
static const char* styleKeyC = "Style";
static const char* fcommentKeyC = "Files2Comment";
static const char* printBriefKeyC = "PrintBrief";
static const char* printShortVarDocKeyC = "PrintShortVarDoc";
static const char* verbosePrintingKeyC = "VerbosePrinting";
static const char* automaticAddReturnType = "AutomaticAddReturnType";
static const char* customBeginKeyC = "CustomBegin";
static const char* customBriefKeyC = "CustomBrief";
static const char* customEmptyLineKeyC = "CustomEmptyLine";
static const char* customNewLineKeyC = "CustomNewLine";
static const char* customEndingKeyC = "CustomEnding";
static const char* customShortDocKeyC = "CustomShortDoc";
static const char* customShortDocEndKeyC = "CustomShortDocEnd";
static const char* fileCommentEnabledKeyC = "FileComments";
static const char* fileCommentHeadersKeyC = "FileCommentHeaders";
static const char* fileCommentImplKeyC = "FileCommentImplementations";
static const char* fileCommentKeyC = "FileComment";

static QString defaultCommand()
{
    QString rc = QLatin1String("doxygen");
#if defined(Q_OS_WIN32)
    rc.append(QLatin1String(".exe"));
#endif
    return rc;
}

static QString defaultWizardCommand()
{
    QString rc = QLatin1String("doxywizard");
#if defined(Q_OS_WIN32)
    rc.append(QLatin1String(".exe"));
#endif
    return rc;
}

static QString defaultDoxyFile()
{
    return QLatin1String("Doxyfile");
}

DoxygenSettingsStruct::DoxygenSettingsStruct()
    : doxyfileFileName(defaultDoxyFile())
    , doxygenCommand(defaultCommand())
    , doxywizardCommand(defaultWizardCommand())
    , style(qtDoc)
    , fcomment(headers)
    , printBrief(true)
    , shortVarDoc(true)
    , verbosePrinting(false)
    , automaticReturnType(true)
{
    qRegisterMetaType<DoxygenSettingsStruct>("DoxygenSettingsStruct");
}

void DoxygenSettingsStruct::fromSettings(Utils::QtcSettings* settings)
{
    settings->beginGroup(Utils::keyFromString(QLatin1String(groupC)));
    doxygenCommand = settings->value(Utils::keyFromString(QLatin1String(commandKeyC)), defaultCommand()).toString();
    doxyfileFileName = settings->value(Utils::keyFromString(QLatin1String(doxyfilePathKeyC)), defaultDoxyFile()).toString();
    doxywizardCommand = settings->value(Utils::keyFromString(QLatin1String(wizardcommandKeyC)), defaultWizardCommand()).toString();
    style = DoxygenStyle(settings->value(Utils::keyFromString(QLatin1String(styleKeyC)), 0).toInt());
    fcomment = Files2Comment(settings->value(Utils::keyFromString(QLatin1String(fcommentKeyC)), 0).toInt());
    printBrief = settings->value(Utils::keyFromString(QLatin1String(printBriefKeyC)), 1).toBool();
    shortVarDoc = settings->value(Utils::keyFromString(QLatin1String(printShortVarDocKeyC)), 1).toBool();
    verbosePrinting = settings->value(Utils::keyFromString(QLatin1String(verbosePrintingKeyC)), 0).toBool();
    automaticReturnType = settings->value(Utils::keyFromString(QLatin1String(automaticAddReturnType)), true).toBool();
    customBegin = settings->value(Utils::keyFromString(QLatin1String(customBeginKeyC)), "").toString();
    customBrief = settings->value(Utils::keyFromString(QLatin1String(customBriefKeyC)), "").toString();
    customEmptyLine = settings->value(Utils::keyFromString(QLatin1String(customEmptyLineKeyC)), "").toString();
    customNewLine = settings->value(Utils::keyFromString(QLatin1String(customNewLineKeyC)), "").toString();
    customEnding = settings->value(Utils::keyFromString(QLatin1String(customEndingKeyC)), "").toString();
    customShortDoc = settings->value(Utils::keyFromString(QLatin1String(customShortDocKeyC)), "").toString();
    customShortDocEnd = settings->value(Utils::keyFromString(QLatin1String(customShortDocEndKeyC)), "").toString();
    fileCommentsEnabled = settings->value(Utils::keyFromString(QLatin1String(fileCommentEnabledKeyC)), false).toBool();
    fileCommentHeaders = settings->value(Utils::keyFromString(QLatin1String(fileCommentHeadersKeyC)), false).toBool();
    fileCommentImpl = settings->value(Utils::keyFromString(QLatin1String(fileCommentImplKeyC)), false).toBool();
    fileComment = settings->value(Utils::keyFromString(QLatin1String(fileCommentKeyC)), "").toString();

    settings->endGroup();

    // Support java, qt and custom styles
    setDoxygenCommentStyle(style);
}

void DoxygenSettingsStruct::toSettings(Utils::QtcSettings* settings)
{
    settings->beginGroup(Utils::keyFromString(QLatin1String(groupC)));
    settings->setValue(Utils::keyFromString(QLatin1String(commandKeyC)), doxygenCommand);
    settings->setValue(Utils::keyFromString(QLatin1String(doxyfilePathKeyC)), doxyfileFileName);
    settings->setValue(Utils::keyFromString(QLatin1String(wizardcommandKeyC)), doxywizardCommand);
    settings->setValue(Utils::keyFromString(QLatin1String(styleKeyC)), style);
    settings->setValue(Utils::keyFromString(QLatin1String(fcommentKeyC)), fcomment);
    settings->setValue(Utils::keyFromString(QLatin1String(printBriefKeyC)), printBrief);
    settings->setValue(Utils::keyFromString(QLatin1String(printShortVarDocKeyC)), shortVarDoc);
    settings->setValue(Utils::keyFromString(QLatin1String(verbosePrintingKeyC)), verbosePrinting);
    settings->setValue(Utils::keyFromString(QLatin1String(automaticAddReturnType)), automaticReturnType);
    settings->setValue(Utils::keyFromString(QLatin1String(customBeginKeyC)), customBegin);
    settings->setValue(Utils::keyFromString(QLatin1String(customBriefKeyC)), customBrief);
    settings->setValue(Utils::keyFromString(QLatin1String(customEmptyLineKeyC)), customEmptyLine);
    settings->setValue(Utils::keyFromString(QLatin1String(customNewLineKeyC)), customNewLine);
    settings->setValue(Utils::keyFromString(QLatin1String(customEndingKeyC)), customEnding);
    settings->setValue(Utils::keyFromString(QLatin1String(customShortDocKeyC)), customShortDoc);
    settings->setValue(Utils::keyFromString(QLatin1String(customShortDocEndKeyC)), customShortDocEnd);
    settings->setValue(Utils::keyFromString(QLatin1String(fileCommentEnabledKeyC)), fileCommentsEnabled);
    settings->setValue(Utils::keyFromString(QLatin1String(fileCommentHeadersKeyC)), fileCommentHeaders);
    settings->setValue(Utils::keyFromString(QLatin1String(fileCommentImplKeyC)), fileCommentImpl);
    settings->setValue(Utils::keyFromString(QLatin1String(fileCommentKeyC)), fileComment);
    settings->endGroup();

    // Support java, qt and custom styles
    setDoxygenCommentStyle(style);
}

bool DoxygenSettingsStruct::equals(const DoxygenSettingsStruct& s) const
{

    return doxygenCommand == s.doxygenCommand
        && doxywizardCommand == s.doxywizardCommand
        && doxyfileFileName == s.doxyfileFileName
        && style == s.style
        && fcomment == s.fcomment
        && printBrief == s.printBrief
        && shortVarDoc == s.shortVarDoc
        && verbosePrinting == s.verbosePrinting
        && automaticReturnType == s.automaticReturnType
        && customBegin == s.customBegin
        && customBrief == s.customBrief
        && customEmptyLine == s.customEmptyLine
        && customNewLine == s.customNewLine
        && customEnding == s.customEnding
        && customShortDoc == s.customShortDoc
        && customShortDocEnd == s.customShortDocEnd
        && fileComment == s.fileComment
        && fileCommentHeaders == s.fileCommentHeaders
        && fileCommentImpl == s.fileCommentImpl
        && fileCommentsEnabled == s.fileCommentsEnabled;
}

QStringList DoxygenSettingsStruct::addOptions(const QStringList& args) const
{
    // TODO, look at possible doxygen args in the manual and act here...
    return args;
}

QString DoxygenSettingsStruct::formatArguments(const QStringList& args)
{
    // TODO find out if it can really be useful or get rid of it
    QString rc;
    QTextStream str(&rc);
    const int size = args.size();
    for (int i = 0; i < size; i++) {
        const QString& arg = args.at(i);
        if (i)
            str << ' ';
        str << arg;
    }

    return rc;
}

void DoxygenSettingsStruct::setDoxygenCommentStyle(DoxygenStyle s)
{
    switch (s) {
    case javaDoc: {
        DoxyComment.doxBegin = "/**\n";
        DoxyComment.doxBrief = " * @brief \n";
        DoxyComment.doxEmptyLine = " *\n";
        DoxyComment.doxNewLine = " * @";
        DoxyComment.doxEnding = " */\n";
        DoxyComment.doxShortVarDoc = " /**< ";
        DoxyComment.doxShortVarDocEnd = " */";
        break;
    }
    case customDoc: {
        DoxyComment.doxBegin = customBegin;
        DoxyComment.doxBrief = customBrief;
        DoxyComment.doxEmptyLine = customEmptyLine;
        DoxyComment.doxNewLine = customNewLine;
        DoxyComment.doxEnding = customEnding;
        DoxyComment.doxShortVarDoc = customShortDoc;
        DoxyComment.doxShortVarDocEnd = customShortDocEnd;
        break;
    }
    default: //case qtDoc:
    {
        DoxyComment.doxBegin = "/*!\n";
        DoxyComment.doxBrief = " \\brief \n";
        DoxyComment.doxEmptyLine = "\n";
        DoxyComment.doxNewLine = " \\";
        DoxyComment.doxEnding = "*/\n";
        DoxyComment.doxShortVarDoc = " /*!< ";
        DoxyComment.doxShortVarDocEnd = " */";
        break;
    }
    }
}
