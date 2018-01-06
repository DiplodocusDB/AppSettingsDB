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

#include "AppSettingsDBXMLNodeImpl.h"

namespace DiplodocusDB
{

AppSettingsDBXMLNodeImpl::AppSettingsDBXMLNodeImpl(const std::string& key,
                                                   std::shared_ptr<AppSettingsDBXMLFileRepositoryImpl> repository,
                                                   pugi::xml_node node)
    : AppSettingsDBNode(key), m_repository(repository), m_node(node)
{
}

void AppSettingsDBXMLNodeImpl::commit()
{
    if (m_dataType.modifier() == EDataTypeModifier::eNone)
    {
        m_node.text().set(m_value.c_str());
    }
    else if (m_dataType.modifier() == EDataTypeModifier::eList)
    {
        for (const std::string& value : m_values)
        {
            pugi::xml_node itemNode = m_node.append_child("item");
            itemNode.text().set(value.c_str());
        }
    }

    m_repository->commit();
}

std::shared_ptr<AppSettingsDBNode> AppSettingsDBXMLNodeImpl::createNode(const std::string& key)
{
    pugi::xml_node newNode = m_node.append_child(key.c_str());
    return std::make_shared<AppSettingsDBXMLNodeImpl>(key, m_repository, newNode);
}

std::shared_ptr<AppSettingsDBNode> AppSettingsDBXMLNodeImpl::getNode(const std::string& key)
{
    std::shared_ptr<AppSettingsDBXMLNodeImpl> result;
    pugi::xml_node node = m_node.child(key.c_str());
    result = std::make_shared<AppSettingsDBXMLNodeImpl>(key, m_repository, node);
    result->m_dataType = DataType(EPrimitiveDataType::eUTF8String);
    result->m_value = node.text().as_string();
    return result;
}

std::shared_ptr<AppSettingsDBNode> AppSettingsDBXMLNodeImpl::getListNode(const std::string& key)
{
    std::shared_ptr<AppSettingsDBXMLNodeImpl> result;
    pugi::xml_node node = m_node.child(key.c_str());
    result = std::make_shared<AppSettingsDBXMLNodeImpl>(key, m_repository, node);

    std::vector<std::string> values;
    for (pugi::xml_node item : node.children("item"))
    {
        values.push_back(item.text().as_string());
    }
    result->m_dataType = DataType(EPrimitiveDataType::eUTF8String, EDataTypeModifier::eList);
    result->m_values = values;

    return result;
}

std::shared_ptr<AppSettingsDBNode> AppSettingsDBXMLNodeImpl::getParentNode(const std::string& key)
{
    std::shared_ptr<AppSettingsDBXMLNodeImpl> result;
    pugi::xml_node node = m_node.child(key.c_str());
    result = std::make_shared<AppSettingsDBXMLNodeImpl>(key, m_repository, node);
    return result;
}

}
