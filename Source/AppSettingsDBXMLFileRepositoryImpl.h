/*
    Copyright (c) 2015-2018 Xavier Leclercq

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
*/

#ifndef _DIPLODOCUSDB_APPSETTINGSDB_APPSETTINGSDBXMLFILEREPOSITORYIMPL_H_
#define _DIPLODOCUSDB_APPSETTINGSDB_APPSETTINGSDBXMLFILEREPOSITORYIMPL_H_

#include "AppSettingsDBNode.h"
#include "DiplodocusDB/Core/VersionNumber.h"
#include <pugixml.hpp>
#include <boost/filesystem/path.hpp>

namespace DiplodocusDB
{

class AppSettingsDBXMLFileRepositoryImpl : public std::enable_shared_from_this<AppSettingsDBXMLFileRepositoryImpl>
{
public:
    AppSettingsDBXMLFileRepositoryImpl();
    ~AppSettingsDBXMLFileRepositoryImpl();

    void create(const VersionNumber& version, const boost::filesystem::path& path);
    void open(const boost::filesystem::path& path);

    std::shared_ptr<AppSettingsDBNode> root();

    void commit();

private:
    boost::filesystem::path m_path;
    pugi::xml_document m_document;
    pugi::xml_node m_rootNode;
    pugi::xml_node m_settingsNode;
};

}

#endif
