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

#include "AppSettingsDBTests.h"
#include "DiplodocusDB/AppSettingsDB/AppSettingsDB.h"
#include "DiplodocusDB/AppSettingsDB/AppSettingsDBXMLFileRepository.h"

void AddAppSettingsDBTests(TestHarness& theTestHarness)
{
    TestSequence& appSettingsDBTestSequence = theTestHarness.appendTestSequence("AppSettingsDB tests");

    new FileComparisonTest("Creation test 1", AppSettingsDBCreationTest1, appSettingsDBTestSequence);
    
    new FileComparisonTest("set test 1", AppSettingsDBSetTest1, appSettingsDBTestSequence);

    new FileComparisonTest("setString test 1", AppSettingsDBSetStringTest1, appSettingsDBTestSequence);

    new FileComparisonTest("setStringList test 1", AppSettingsDBSetStringListTest1, appSettingsDBTestSequence);
    new FileComparisonTest("setStringList test 2", AppSettingsDBSetStringListTest2, appSettingsDBTestSequence);
}

TestResult::EOutcome AppSettingsDBCreationTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "AppSettingsDBCreationTest1.xml");

    std::shared_ptr<DiplodocusDB::AppSettingsDBXMLFileRepository> repository = std::make_shared<DiplodocusDB::AppSettingsDBXMLFileRepository>();
    repository->create(DiplodocusDB::VersionNumber(1, 0, 0), outputPath);

    DiplodocusDB::AppSettingsDB appSettings(repository);

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "AppSettingsDBCreationTest1.xml");

    return TestResult::ePassed;
}

TestResult::EOutcome AppSettingsDBSetTest1(FileComparisonTest& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "AppSettingsDBSetTest1.xml");

    std::shared_ptr<DiplodocusDB::AppSettingsDBXMLFileRepository> repository = std::make_shared<DiplodocusDB::AppSettingsDBXMLFileRepository>();
    repository->create(DiplodocusDB::VersionNumber(1, 0, 0), outputPath);

    DiplodocusDB::AppSettingsDB appSettings(repository);

    Ishiko::Error error;
    appSettings.set("key1", "value1", error);

    if (!error)
    {
        std::string value = appSettings.getString("key1", error);
        if (!error && (value == "value1"))
        {
            result = TestResult::ePassed;
        }
    }

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "AppSettingsDBSetTest1.xml");

    return result;
}

TestResult::EOutcome AppSettingsDBSetStringTest1(FileComparisonTest& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "AppSettingsDBSetStringTest1.xml");

    std::shared_ptr<DiplodocusDB::AppSettingsDBXMLFileRepository> repository = std::make_shared<DiplodocusDB::AppSettingsDBXMLFileRepository>();
    repository->create(DiplodocusDB::VersionNumber(1, 0, 0), outputPath);

    DiplodocusDB::AppSettingsDB appSettings(repository);

    Ishiko::Error error;
    appSettings.setString("key1", "value1", error);

    if (!error)
    {
        std::string value = appSettings.getString("key1", error);
        if (!error && (value == "value1"))
        {
            result = TestResult::ePassed;
        }
    }

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "AppSettingsDBSetStringTest1.xml");

    return result;
}

TestResult::EOutcome AppSettingsDBSetStringListTest1(FileComparisonTest& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "AppSettingsDBSetStringListTest1.xml");

    std::shared_ptr<DiplodocusDB::AppSettingsDBXMLFileRepository> repository = std::make_shared<DiplodocusDB::AppSettingsDBXMLFileRepository>();
    repository->create(DiplodocusDB::VersionNumber(1, 0, 0), outputPath);

    DiplodocusDB::AppSettingsDB appSettings(repository);

    Ishiko::Error error;
    appSettings.setStringList("key1", std::vector<std::string>(), error);

    if (!error)
    {
        std::vector<std::string> returnedValues;
        appSettings.getStringList("key1", returnedValues, error);
        if (!error && returnedValues.empty())
        {
            result = TestResult::ePassed;
        }
    }

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "AppSettingsDBSetStringListTest1.xml");

    return result;
}

TestResult::EOutcome AppSettingsDBSetStringListTest2(FileComparisonTest& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    std::shared_ptr<DiplodocusDB::AppSettingsDBXMLFileRepository> repository = std::make_shared<DiplodocusDB::AppSettingsDBXMLFileRepository>();
    DiplodocusDB::AppSettingsDB appSettings(repository);

    Ishiko::Error error;
    std::vector<std::string> values = { "value1" };
    appSettings.setStringList("key1", values, error);

    if (!error)
    {
        std::vector<std::string> returnedValues;
        appSettings.getStringList("key1", returnedValues, error);
        if (!error && (returnedValues.size() == 1))
        {
            result = TestResult::ePassed;
        }
    }

    return result;
}
