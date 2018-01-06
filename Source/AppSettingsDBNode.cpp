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

#include "AppSettingsDBNode.h"

namespace DiplodocusDB
{

AppSettingsDBNode::AppSettingsDBNode(const std::string& key)
    : m_key(key), m_dataType(EPrimitiveDataType::eNULL)
{
}

AppSettingsDBNode::~AppSettingsDBNode()
{
}

bool AppSettingsDBNode::getBool(const std::string& key,
                                Ishiko::Error& error) const
{
    bool result;

    std::shared_ptr<AppSettingsDBNode> node = const_cast<AppSettingsDBNode*>(this)->getNode(key);
    if (node)
    {
        result = (node->m_value == "true");
    }
    else
    {
        error = -1;
    }

    return result;
}

std::string AppSettingsDBNode::getString(const std::string& key,
                                         Ishiko::Error& error) const
{
    std::string result;

    std::shared_ptr<AppSettingsDBNode> node = const_cast<AppSettingsDBNode*>(this)->getNode(key);
    if (node)
    {
        result = node->m_value;
    }
    else
    {
        error = -1;
    }

    return result;
}

void AppSettingsDBNode::getStringList(const std::string& key,
                                      std::vector<std::string>& values,
                                      Ishiko::Error& error) const
{
    std::shared_ptr<AppSettingsDBNode> node = const_cast<AppSettingsDBNode*>(this)->getListNode(key);
    if (node)
    {
        values.insert(values.end(), node->m_values.begin(), node->m_values.end());
    }
    else
    {
        error = -1;
    }
}

std::shared_ptr<AppSettingsDBNode> AppSettingsDBNode::getParentNode(const std::string& key,
                                                                    Ishiko::Error& error)
{
    std::shared_ptr<AppSettingsDBNode> node = const_cast<AppSettingsDBNode*>(this)->getParentNode(key);
    if (!node)
    {
        error = -1;
    }
    return node;
}

void AppSettingsDBNode::setBool(const std::string& key,
                                bool value,
                                Ishiko::Error& error)
{
    set(key, (value ? "true" : "false"), error);
}

void AppSettingsDBNode::setString(const std::string& key,
                                  const std::string& value,
                                  Ishiko::Error& error)
{
    set(key, value, error);
}

void AppSettingsDBNode::setStringList(const std::string& key,
                                      const std::vector<std::string>& values,
                                      Ishiko::Error& error)
{
    try
    {
        std::shared_ptr<AppSettingsDBNode> newNode = createNode(key);
        newNode->m_dataType = DataType(EPrimitiveDataType::eUTF8String, EDataTypeModifier::eList);
        newNode->m_values = values;
        newNode->commit();
    }
    catch (...)
    {
        error = -1;
    }
}

void AppSettingsDBNode::setParentNode(const std::string& key,
                                      Ishiko::Error& error)
{
    try
    {
        std::shared_ptr<AppSettingsDBNode> newNode = createNode(key);
        newNode->commit();
    }
    catch (...)
    {
        error = -1;
    }
}

void AppSettingsDBNode::set(const std::string& key,
                            const std::string& value,
                            Ishiko::Error& error)
{
    try
    {
        std::shared_ptr<AppSettingsDBNode> newNode = createNode(key);
        newNode->m_dataType = DataType(EPrimitiveDataType::eUTF8String);
        newNode->m_value = value;
        newNode->commit();
    }
    catch (...)
    {
        error = -1;
    }
}

}
