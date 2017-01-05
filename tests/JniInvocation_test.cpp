/*
 * Copyright (C) 2014 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "NativeBridge_test"

#include <linux/limits.h> /* for PATH_MAX */

#include <nativehelper/JniInvocation.h>
#include <gtest/gtest.h>


#include "string.h"

// PROPERTY_VALUE_MAX.
#include "cutils/properties.h"

#include <bionic/bionic.h>
// Ability to have fake local system properties.
#define _REALLY_INCLUDE_BIONIC_PROPERTIES_IMPL_H_
#include <bionic/properties_impl.h>

extern void *__system_property_area__;

struct LocalPropertyTestState {
    LocalPropertyTestState() : valid(false) {
        char dir_template[PATH_MAX];
        snprintf(dir_template, sizeof(dir_template), "/tmp/prop-XXXXXX");
        char* dirname = mkdtemp(dir_template);
        if (!dirname) {
            fprintf(stderr, "making temp file for test state failed (is %s writable?): %s",
                    dir_template, strerror(errno));
            return;
        }

        old_pa = __system_property_area__;
        __system_property_area__ = NULL;

        pa_dirname = dirname;
        pa_filename = pa_dirname + "/__properties__";

        __system_property_set_filename(pa_filename.c_str());
        __system_property_area_init();
        valid = true;
    }

    ~LocalPropertyTestState() {
        if (!valid) {
            return;
        }

        __system_property_area__ = old_pa;

        __system_property_set_filename(PROP_FILENAME);
        unlink(pa_filename.c_str());
        rmdir(pa_dirname.c_str());
    }
public:
    bool valid;
private:
    std::string pa_dirname;
    std::string pa_filename;
    void *old_pa;
};

namespace android {

class JNIInvocationTest : public testing::Test {
};

static const char* kDebuggableSystemProperty = "ro.debuggable";
static const char* kIsDebuggableValue = "1";
static const char* kIsNotDebuggableValue = "0";

static const char* kLibrarySystemProperty = "persist.sys.dalvik.vm.lib.2";
static const char* kTestNonNull = "libartd.so";
static const char* kTestNonNull2 = "libartd2.so";
static const char* kExpected = "libart.so";

TEST_F(JNIInvocationTest, Debuggable) {
    LocalPropertyTestState pa;
    ASSERT_TRUE(pa.valid);
    ASSERT_EQ(0, __system_property_add(kDebuggableSystemProperty, 13, kIsDebuggableValue, 1));
    ASSERT_EQ(0, __system_property_add(kLibrarySystemProperty, 27, kTestNonNull2, 11));

    char buffer[PROPERTY_VALUE_MAX];
    const char* result = JniInvocation::GetLibrary(NULL, buffer);
    EXPECT_FALSE(result == NULL);
    if (result != NULL) {
        EXPECT_TRUE(strcmp(result, kTestNonNull2) == 0);
        EXPECT_FALSE(strcmp(result, kExpected) == 0);
    }

    result = JniInvocation::GetLibrary(kTestNonNull, buffer);
    EXPECT_FALSE(result == NULL);
    if (result != NULL) {
        EXPECT_TRUE(strcmp(result, kTestNonNull) == 0);
        EXPECT_FALSE(strcmp(result, kTestNonNull2) == 0);
    }
}

TEST_F(JNIInvocationTest, NonDebuggable) {
    LocalPropertyTestState pa;
    ASSERT_TRUE(pa.valid);
    ASSERT_EQ(0, __system_property_add(kDebuggableSystemProperty, 13, kIsNotDebuggableValue, 1));

    char buffer[PROPERTY_VALUE_MAX];
    const char* result = JniInvocation::GetLibrary(NULL, buffer);
    EXPECT_FALSE(result == NULL);
    if (result != NULL) {
        EXPECT_TRUE(strcmp(result, kExpected) == 0);
        EXPECT_FALSE(strcmp(result, kTestNonNull) == 0);
        EXPECT_FALSE(strcmp(result, kTestNonNull2) == 0);
    }

    result = JniInvocation::GetLibrary(kTestNonNull, buffer);
    EXPECT_FALSE(result == NULL);
    if (result != NULL) {
        EXPECT_TRUE(strcmp(result, kExpected) == 0);
        EXPECT_FALSE(strcmp(result, kTestNonNull) == 0);
    }
}

}  // namespace android
