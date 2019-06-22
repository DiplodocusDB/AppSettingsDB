/*
    Copyright (c) 2017-2019 Xavier Leclercq

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

#include "AppSettingsDBXMLFileRepositoryTests.h"
#include "DiplodocusDB/AppSettingsDB/AppSettingsDBXMLFileRepository.h"

using namespace Ishiko::Tests;
using namespace boost::filesystem;

AppSettingsDBXMLFileRepositoryTests::AppSettingsDBXMLFileRepositoryTests(const TestNumber& number,
    const TestEnvironment& environment)
    : TestSequence(number, "AppSettingsDBXMLFileRepository tests", environment)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<FileComparisonTest>("create test 1", CreateTest1);
    append<HeapAllocationErrorsTest>("open test 1", OpenTest1);
}

void AppSettingsDBXMLFileRepositoryTests::ConstructorTest1(Test& test)
{
    DiplodocusDB::AppSettingsDBXMLFileRepository repository;

    ISHTF_PASS();
}

// Test creation of XML file when the file doesn't exist yet
void AppSettingsDBXMLFileRepositoryTests::CreateTest1(FileComparisonTest& test)
{
    path outputPath(test.environment().getTestOutputDirectory()
        / "AppSettingsDBXMLFileRepositoryTests_CreateTest1.xml");

    DiplodocusDB::AppSettingsDBXMLFileRepository repository;
    repository.create(DiplodocusDB::VersionNumber(1, 0, 0), outputPath);

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory()
        / "AppSettingsDBXMLFileRepositoryTests_CreateTest1.xml");

    ISHTF_PASS();
}

void AppSettingsDBXMLFileRepositoryTests::OpenTest1(Test& test)
{
    path inputPath(test.environment().getTestDataDirectory() / "AppSettingsDBXMLFileRepositoryTests_OpenTest1.xml");

    DiplodocusDB::AppSettingsDBXMLFileRepository repository;
    repository.open(inputPath);

    ISHTF_FAIL_UNLESS(repository.root());
    ISHTF_PASS();
}
