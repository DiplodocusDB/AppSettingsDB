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

#ifndef _DIPLODOCUSDB_APPSETTINGSDB_APPSETTINGSDB_H_
#define _DIPLODOCUSDB_APPSETTINGSDB_APPSETTINGSDB_H_

#include "AppSettingsDBRepository.h"
#include "AppSettingsDBNode.h"
#include "Ishiko/Errors/Error.h"
#include <vector>
#include <string>
#include <memory>

namespace DiplodocusDB
{

class AppSettingsDB
{
public:
    AppSettingsDB(std::shared_ptr<AppSettingsDBRepository> repository);
    ~AppSettingsDB();

    bool getBool(const std::string& key, Ishiko::Error& error) const;
    std::string getString(const std::string& key, Ishiko::Error& error) const;
    void getStringList(const std::string& key, std::vector<std::string>& values, Ishiko::Error& error) const;

    std::shared_ptr<AppSettingsDBNode> getParentNode(const std::string& key, Ishiko::Error& error);
    
    void setBool(const std::string& key, bool value, Ishiko::Error& error);
    void setString(const std::string& key, const std::string& value, Ishiko::Error& error);
    void setStringList(const std::string& key, const std::vector<std::string>& values, Ishiko::Error& error);

    void setParentNode(const std::string& key, Ishiko::Error& error);

private:
    void set(const std::string& key, const std::string& value, Ishiko::Error& error);

private:
    std::shared_ptr<AppSettingsDBRepository> m_repository;
};

}

#include "linkoptions.h"

#endif
