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

    new HeapAllocationErrorsTest("Creation test 1", AppSettingsDBCreationTest1, appSettingsDBTestSequence);
    
    new HeapAllocationErrorsTest("set test 1", AppSettingsDBSetTest1, appSettingsDBTestSequence);

    new HeapAllocationErrorsTest("setString test 1", AppSettingsDBSetStringTest1, appSettingsDBTestSequence);
}

TestResult::EOutcome AppSettingsDBCreationTest1()
{
    std::shared_ptr<DiplodocusDB::AppSettingsDBXMLFileRepository> repository = std::make_shared<DiplodocusDB::AppSettingsDBXMLFileRepository>();
    DiplodocusDB::AppSettingsDB appSettings(repository);
    return TestResult::ePassed;
}

TestResult::EOutcome AppSettingsDBSetTest1()
{
    TestResult::EOutcome result = TestResult::eFailed;

    std::shared_ptr<DiplodocusDB::AppSettingsDBXMLFileRepository> repository = std::make_shared<DiplodocusDB::AppSettingsDBXMLFileRepository>();
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

    return result;
}

TestResult::EOutcome AppSettingsDBSetStringTest1()
{
    TestResult::EOutcome result = TestResult::eFailed;

    std::shared_ptr<DiplodocusDB::AppSettingsDBXMLFileRepository> repository = std::make_shared<DiplodocusDB::AppSettingsDBXMLFileRepository>();
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

    return result;
}
