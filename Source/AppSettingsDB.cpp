/*
    Copyright (c) 2015-1018 Xavier Leclercq

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

#include "AppSettingsDB.h"

namespace DiplodocusDB
{

AppSettingsDB::AppSettingsDB(std::shared_ptr<AppSettingsDBRepository> repository)
    : m_repository(repository), m_root("root")
{
}

AppSettingsDB::~AppSettingsDB()
{
}

std::string AppSettingsDB::getString(const std::string& key,
                                     Ishiko::Error& error) const
{
    std::string result;

    bool found = false;
    for (std::shared_ptr<AppSettingsDBNode> node : m_root.m_children)
    {
        if (node->m_key == key)
        {
            result = node->m_value;
            found = true;
        }
    }
    if (!found)
    {
        error = -1;
    }
    return result;
}

void AppSettingsDB::setString(const std::string& key,
                              const std::string& value,
                              Ishiko::Error& error)
{
    set(key, value, error);
}

void AppSettingsDB::set(const std::string& key,
                        const std::string& value,
                        Ishiko::Error& error)
{
    try
    {
        std::shared_ptr<AppSettingsDBNode> newNode = m_repository->createNode(key);
        newNode->m_dataType = EPrimitiveDataTypes::eUTF8String;
        newNode->m_value = value;
        m_root.m_children.push_back(newNode);
    }
    catch (...)
    {
        error = -1;
    }
}

}
