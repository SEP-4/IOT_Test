#include "gtest/gtest.h"
#include "fff/fff.h"
#include "FreeRTOS_FFF_MocksDeclaration.h"
DEFINE_FFF_GLOBALS

extern "C" {
#include <stdio.h>

//Simulated FreeRTOs header files belonging to the test project
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "rc_servo.h"
#include "Configuration.h"
#include "../../../4.Semester/WindowController.h"
SemaphoreHandle_t semaphore_mutex = (SemaphoreHandle_t) 100;
}



// --- Create Mocks ---
//SemaphoreHandle_t get_mutex();
FAKE_VALUE_FUNC(SemaphoreHandle_t, get_mutex);
//void rc_servo_setPosition(uint8_t servoNo, int8_t percent);
FAKE_VOID_FUNC(rc_servo_setPosition, uint8_t, int8_t);
//uint8_t configuration_get_windows_data();
FAKE_VALUE_FUNC(uint8_t, configuration_get_windows_data);


//--------------------------------------------------------------------------------------------------
class WindowControllerTest : public ::testing::Test {
protected:
	void SetUp() override {
		RESET_FAKE(xSemaphoreTake);
		RESET_FAKE(get_mutex);
		RESET_FAKE(xSemaphoreGive);
		RESET_FAKE(rc_servo_setPosition);
		RESET_FAKE(configuration_get_windows_data);
		FFF_RESET_HISTORY();
	}
	void TearDown() override {}
};

TEST_F(WindowControllerTest, InitialisationIsCorrect) {
	//ARRANGE
	void *pvParamaters;
	//ACT
	WindowController_init(pvParamaters);
	//ASSERT
	EXPECT_EQ(1, get_mutex_fake.call_count);
	EXPECT_EQ(1, xSemaphoreGive_fake.call_count);
}

TEST_F(WindowControllerTest, RunningIsCorrect) {
	//ARRANGE
	//ACT
	WindowController_run();
	//ASSERT

	EXPECT_EQ(1, xSemaphoreTake_fake.call_count);

	//Arguments correct?
	EXPECT_TRUE(semaphore_mutex == xSemaphoreTake_fake.arg0_val);

	EXPECT_EQ(1, configuration_get_windows_data_fake.call_count);

	EXPECT_EQ(1,rc_servo_setPosition_fake.call_count);

	//Arguments correct? 
	EXPECT_EQ(0, rc_servo_setPosition_fake.arg0_val);
}

