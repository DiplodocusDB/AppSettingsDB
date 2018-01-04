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
    appendDataTypeNode(m_dataType, m_node);

    pugi::xml_node valueNode = m_node.append_child("value");
    if (m_dataType.modifier() == EDataTypeModifier::eNone)
    {
        valueNode.text().set(m_value.c_str());
    }

    m_repository->commit();
}

void AppSettingsDBXMLNodeImpl::appendDataTypeNode(const DataType& type, 
                                                  pugi::xml_node parentNode)
{
    pugi::xml_node typeNode = parentNode.append_child("data-type");
    pugi::xml_node primitiveTypeNode = typeNode.append_child("primary-data-type");

    std::string primitiveDataTypeString;
    switch (type.primitiveType())
    {
    case EPrimitiveDataType::eUTF8String:
        primitiveDataTypeString = "UTF8String";
        break;
    }
    primitiveTypeNode.text().set(primitiveDataTypeString.c_str());

    std::string modifierString;
    switch (type.modifier())
    {
    case EDataTypeModifier::eList:
        modifierString = "list";
        break;
    }
    if (!modifierString.empty())
    {
        pugi::xml_node modifierNode = typeNode.append_child("modifier");
        modifierNode.text().set(modifierString.c_str());
    }
}

}
