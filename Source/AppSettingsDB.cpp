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

#include "AppSettingsDB.h"

namespace DiplodocusDB
{

AppSettingsDB::AppSettingsDB(std::shared_ptr<AppSettingsDBRepository> repository)
    : m_repository(repository)
{
}

AppSettingsDB::~AppSettingsDB()
{
}

bool AppSettingsDB::getBool(const std::string& key,
                            Ishiko::Error& error) const
{
    return m_repository->root()->getBool(key, error);
}

std::string AppSettingsDB::getString(const std::string& key,
                                     Ishiko::Error& error) const
{
    return m_repository->root()->getString(key, error);
}

void AppSettingsDB::getStringList(const std::string& key,
                                  std::vector<std::string>& values,
                                  Ishiko::Error& error) const
{
    return m_repository->root()->getStringList(key, values, error);
}

std::shared_ptr<AppSettingsDBNode> AppSettingsDB::getParentNode(const std::string& key, Ishiko::Error& error)
{
    std::shared_ptr<AppSettingsDBNode> node = m_repository->getParentNode(key);
    if (!node)
    {
        error = -1;
    }
    return node;
}

void AppSettingsDB::setBool(const std::string& key,
                            bool value, 
                            Ishiko::Error& error)
{
    m_repository->root()->setBool(key, value, error);
}

void AppSettingsDB::setString(const std::string& key,
                              const std::string& value,
                              Ishiko::Error& error)
{
    m_repository->root()->setString(key, value, error);
}

void AppSettingsDB::setStringList(const std::string& key,
                                  const std::vector<std::string>& values,
                                  Ishiko::Error& error)
{
    m_repository->root()->setStringList(key, values, error);
}

void AppSettingsDB::setParentNode(const std::string& key,
                                  Ishiko::Error& error)
{
    try
    {
        std::shared_ptr<AppSettingsDBNode> newNode = m_repository->createNode(key);
        newNode->commit();
    }
    catch (...)
    {
        error = -1;
    }
}

void AppSettingsDB::set(const std::string& key,
                        const std::string& value,
                        Ishiko::Error& error)
{
    try
    {
        std::shared_ptr<AppSettingsDBNode> newNode = m_repository->createNode(key);
        newNode->setString(value);
        newNode->commit();
    }
    catch (...)
    {
        error = -1;
    }
}

}
