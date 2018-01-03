/*
    Copyright (c) 2017 Xavier Leclercq

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

#include "DiplodocusDB/Core/PrimitiveDataTypes.h"
#include <vector>
#include <memory>

namespace DiplodocusDB
{

class AppSettingsDBNode
{
public:
    AppSettingsDBNode(const std::string& key);
    ~AppSettingsDBNode();

    void setString(const std::string& value);

    std::string m_key;
    EPrimitiveDataTypes m_dataType;
    std::string m_value;
    std::vector<std::shared_ptr<AppSettingsDBNode> > m_children;
};

}

#endif
