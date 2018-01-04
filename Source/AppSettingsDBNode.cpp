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

const std::string& AppSettingsDBNode::value() const
{
    return m_value;
}

const std::vector<std::string>& AppSettingsDBNode::values() const
{
    return m_values;
}

void AppSettingsDBNode::setString(const std::string& value)
{
    m_dataType = DataType(EPrimitiveDataType::eUTF8String);
    m_value = value;
}

void AppSettingsDBNode::setStringList(const std::vector<std::string>& values)
{
    m_dataType = DataType(EPrimitiveDataType::eUTF8String, EDataTypeModifier::eList);
    m_values = values;
}

}
