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

#ifndef _DIPLODOCUSDB_APPSETTINGSDB_APPSETTINGSDBNODE_H_
#define _DIPLODOCUSDB_APPSETTINGSDB_APPSETTINGSDBNODE_H_

#include "DiplodocusDB/Core/DataType.h"
#include "Ishiko/Errors/Error.h"
#include <vector>
#include <memory>

namespace DiplodocusDB
{

class AppSettingsDBNode
{
public:
    AppSettingsDBNode(const std::string& key);
    virtual ~AppSettingsDBNode();

    const std::string& value() const;
    const std::vector<std::string>& values() const;

    void setString(const std::string& value);
    void setStringList(const std::vector<std::string>& values);

    bool getBool(const std::string& key, Ishiko::Error& error) const;

    void setBool(const std::string& key, bool value, Ishiko::Error& error);

    virtual void commit() = 0;

private:
    void set(const std::string& key, const std::string& value, Ishiko::Error& error);

    virtual std::shared_ptr<AppSettingsDBNode> createNode(const std::string& key) = 0;
    virtual std::shared_ptr<AppSettingsDBNode> getNode(const std::string& key) = 0;

protected:
    std::string m_key;
    DataType m_dataType;
    std::string m_value;
    std::vector<std::string> m_values;
};

}

#endif
