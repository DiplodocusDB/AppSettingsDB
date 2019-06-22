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

#include "AppSettingsDBTests.h"
#include "DiplodocusDB/AppSettingsDB/AppSettingsDB.h"
#include "DiplodocusDB/AppSettingsDB/AppSettingsDBXMLFileRepository.h"

using namespace Ishiko::Tests;
using namespace boost::filesystem;

AppSettingsDBTests::AppSettingsDBTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "AppSettingsDB tests", environment)
{
    append<FileComparisonTest>("Constructor test 1", ConstructorTest1);
    append<FileComparisonTest>("setBool test 1", SetBoolTest1);
    append<FileComparisonTest>("setString test 1", SetStringTest1);
    append<FileComparisonTest>("setStringList test 1", SetStringListTest1);
    append<FileComparisonTest>("setStringList test 2", SetStringListTest2);
    append<FileComparisonTest>("setStringList test 3", SetStringListTest3);
    append<FileComparisonTest>("setParentNode test 1", SetParentNodeTest1);
    append<HeapAllocationErrorsTest>("getBool test 1", GetBoolTest1);
    append<HeapAllocationErrorsTest>("getString test 1", GetStringTest1);
}

void AppSettingsDBTests::ConstructorTest1(FileComparisonTest& test)
{
    path outputPath(test.environment().getTestOutputDirectory() / "AppSettingsDBTests_ConstructorTest1.xml");

    std::shared_ptr<DiplodocusDB::AppSettingsDBXMLFileRepository> repository =
        std::make_shared<DiplodocusDB::AppSettingsDBXMLFileRepository>();
    repository->create(DiplodocusDB::VersionNumber(1, 0, 0), outputPath);

    DiplodocusDB::AppSettingsDB appSettings(repository);

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory()
        / "AppSettingsDBTests_ConstructorTest1.xml");

    ISHTF_PASS();
}

void AppSettingsDBTests::SetBoolTest1(FileComparisonTest& test)
{
    path outputPath(test.environment().getTestOutputDirectory() / "AppSettingsDBTests_SetBoolTest1.xml");

    std::shared_ptr<DiplodocusDB::AppSettingsDBXMLFileRepository> repository =
        std::make_shared<DiplodocusDB::AppSettingsDBXMLFileRepository>();
    repository->create(DiplodocusDB::VersionNumber(1, 0, 0), outputPath);

    DiplodocusDB::AppSettingsDB appSettings(repository);

    Ishiko::Error error(0);
    appSettings.setBool("key1", true, error);

    ISHTF_FAIL_IF(error);

    bool value = appSettings.getBool("key1", error);

    ISHTF_FAIL_IF(error);
    ISHTF_FAIL_UNLESS(value == true);

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "AppSettingsDBTests_SetBoolTest1.xml");

    ISHTF_PASS();
}

void AppSettingsDBTests::SetStringTest1(FileComparisonTest& test)
{
    path outputPath(test.environment().getTestOutputDirectory() / "AppSettingsDBTests_SetStringTest1.xml");

    std::shared_ptr<DiplodocusDB::AppSettingsDBXMLFileRepository> repository = std::make_shared<DiplodocusDB::AppSettingsDBXMLFileRepository>();
    repository->create(DiplodocusDB::VersionNumber(1, 0, 0), outputPath);

    DiplodocusDB::AppSettingsDB appSettings(repository);

    Ishiko::Error error(0);
    appSettings.setString("key1", "value1", error);

    ISHTF_FAIL_IF(error);
    
    std::string value = appSettings.getString("key1", error);

    ISHTF_FAIL_IF(error);
    ISHTF_FAIL_UNLESS(value == "value1");
    
    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory()
        / "AppSettingsDBTests_SetStringTest1.xml");

    ISHTF_PASS();
}

void AppSettingsDBTests::SetStringListTest1(FileComparisonTest& test)
{
    path outputPath(test.environment().getTestOutputDirectory() / "AppSettingsDBTests_SetStringListTest1.xml");

    std::shared_ptr<DiplodocusDB::AppSettingsDBXMLFileRepository> repository =
        std::make_shared<DiplodocusDB::AppSettingsDBXMLFileRepository>();
    repository->create(DiplodocusDB::VersionNumber(1, 0, 0), outputPath);

    DiplodocusDB::AppSettingsDB appSettings(repository);

    Ishiko::Error error(0);
    appSettings.setStringList("key1", std::vector<std::string>(), error);

    ISHTF_FAIL_IF(error);

    std::vector<std::string> returnedValues;
    appSettings.getStringList("key1", returnedValues, error);

    ISHTF_FAIL_IF(error);
    ISHTF_FAIL_UNLESS(returnedValues.empty());

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory()
        / "AppSettingsDBTests_SetStringListTest1.xml");

    ISHTF_PASS();
}

void AppSettingsDBTests::SetStringListTest2(FileComparisonTest& test)
{
    path outputPath(test.environment().getTestOutputDirectory() / "AppSettingsDBTests_SetStringListTest2.xml");

    std::shared_ptr<DiplodocusDB::AppSettingsDBXMLFileRepository> repository =
        std::make_shared<DiplodocusDB::AppSettingsDBXMLFileRepository>();
    repository->create(DiplodocusDB::VersionNumber(1, 0, 0), outputPath);

    DiplodocusDB::AppSettingsDB appSettings(repository);

    Ishiko::Error error(0);
    std::vector<std::string> values = { "value1" };
    appSettings.setStringList("key1", values, error);

    ISHTF_FAIL_IF(error);
    
    std::vector<std::string> returnedValues;
    appSettings.getStringList("key1", returnedValues, error);

    ISHTF_FAIL_IF(error);
    ISHTF_ABORT_UNLESS(returnedValues.size() == 1);
    ISHTF_FAIL_UNLESS(returnedValues[0] == "value1");
    
    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory()
        / "AppSettingsDBTests_SetStringListTest2.xml");

    ISHTF_PASS();
}

void AppSettingsDBTests::SetStringListTest3(FileComparisonTest& test)
{
    path outputPath(test.environment().getTestOutputDirectory() / "AppSettingsDBTests_SetStringListTest3.xml");

    std::shared_ptr<DiplodocusDB::AppSettingsDBXMLFileRepository> repository =
        std::make_shared<DiplodocusDB::AppSettingsDBXMLFileRepository>();
    repository->create(DiplodocusDB::VersionNumber(1, 0, 0), outputPath);

    DiplodocusDB::AppSettingsDB appSettings(repository);

    Ishiko::Error error(0);
    std::vector<std::string> values = { "value1", "value2" };
    appSettings.setStringList("key1", values, error);

    ISHTF_FAIL_IF(error);
    
    std::vector<std::string> returnedValues;
    appSettings.getStringList("key1", returnedValues, error);

    ISHTF_FAIL_IF(error);
    ISHTF_ABORT_UNLESS(returnedValues.size() == 2);
    ISHTF_FAIL_UNLESS(returnedValues[0] == "value1");
    ISHTF_FAIL_UNLESS(returnedValues[1] == "value2");
    
    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory()
        / "AppSettingsDBTests_SetStringListTest3.xml");

    ISHTF_PASS();
}

void AppSettingsDBTests::SetParentNodeTest1(FileComparisonTest& test)
{
    path outputPath(test.environment().getTestOutputDirectory() / "AppSettingsDBTests_SetParentNodeTest1.xml");

    std::shared_ptr<DiplodocusDB::AppSettingsDBXMLFileRepository> repository =
        std::make_shared<DiplodocusDB::AppSettingsDBXMLFileRepository>();
    repository->create(DiplodocusDB::VersionNumber(1, 0, 0), outputPath);

    DiplodocusDB::AppSettingsDB appSettings(repository);

    Ishiko::Error error(0);
    appSettings.setParentNode("key1", error);

    ISHTF_FAIL_IF(error);
    
    std::shared_ptr<DiplodocusDB::AppSettingsDBNode> node = appSettings.getParentNode("key1", error);

    ISHTF_FAIL_IF(error);
    ISHTF_FAIL_UNLESS(node);
    
    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory()
        / "AppSettingsDBTests_SetParentNodeTest1.xml");

    ISHTF_PASS();
}

void AppSettingsDBTests::GetBoolTest1(Test& test)
{
    path inputPath(test.environment().getTestDataDirectory() / "AppSettingsDBTests_GetBoolTest1.xml");

    std::shared_ptr<DiplodocusDB::AppSettingsDBXMLFileRepository> repository =
        std::make_shared<DiplodocusDB::AppSettingsDBXMLFileRepository>();
    repository->open(inputPath);

    DiplodocusDB::AppSettingsDB appSettings(repository);

    Ishiko::Error error(0);
    bool value = appSettings.getBool("key1", error);

    ISHTF_FAIL_IF(error);
    ISHTF_FAIL_UNLESS(value == true);
    ISHTF_PASS();
}

void AppSettingsDBTests::GetStringTest1(Test& test)
{
    path inputPath(test.environment().getTestDataDirectory() / "AppSettingsDBTests_GetStringTest1.xml");

    std::shared_ptr<DiplodocusDB::AppSettingsDBXMLFileRepository> repository = std::make_shared<DiplodocusDB::AppSettingsDBXMLFileRepository>();
    repository->open(inputPath);

    DiplodocusDB::AppSettingsDB appSettings(repository);

    Ishiko::Error error(0);
    std::string value = appSettings.getString("key1", error);

    ISHTF_FAIL_IF(error);
    ISHTF_FAIL_UNLESS(value == "value1");
    ISHTF_PASS();
}
