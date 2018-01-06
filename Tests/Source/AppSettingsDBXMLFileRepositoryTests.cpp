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

#include "AppSettingsDBXMLFileRepositoryTests.h"
#include "DiplodocusDB/AppSettingsDB/AppSettingsDBXMLFileRepository.h"

void AddAppSettingsDBXMLFileRepositoryTests(TestHarness& theTestHarness)
{
    TestSequence& repositoryTestSequence = theTestHarness.appendTestSequence("AppSettingsDBXMLFileRepository tests");

    new HeapAllocationErrorsTest("Creation test 1", AppSettingsDBXMLFileRepositoryCreationTest1, repositoryTestSequence);

    new FileComparisonTest("create test 1", AppSettingsDBXMLFileRepositoryCreateTest1, repositoryTestSequence);

    new HeapAllocationErrorsTest("open test 1", AppSettingsDBXMLFileRepositoryOpenTest1, repositoryTestSequence);
}

TestResult::EOutcome AppSettingsDBXMLFileRepositoryCreationTest1()
{
    DiplodocusDB::AppSettingsDBXMLFileRepository repository;
    return TestResult::ePassed;
}

// Test creation of XML file when the file doesn't exist yet
TestResult::EOutcome AppSettingsDBXMLFileRepositoryCreateTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "AppSettingsDBXMLFileRepositoryCreateTest1.xml");

    DiplodocusDB::AppSettingsDBXMLFileRepository repository;
    repository.create(DiplodocusDB::VersionNumber(1, 0, 0), outputPath);

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataDirectory() / "AppSettingsDBXMLFileRepositoryCreateTest1.xml");

    return TestResult::ePassed;
}

TestResult::EOutcome AppSettingsDBXMLFileRepositoryOpenTest1(Test& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "AppSettingsDBXMLFileRepositoryOpenTest1.xml");

    DiplodocusDB::AppSettingsDBXMLFileRepository repository;
    repository.open(inputPath);

    if (repository.root())
    {
        result = TestResult::ePassed;
    }

    return result;
}
