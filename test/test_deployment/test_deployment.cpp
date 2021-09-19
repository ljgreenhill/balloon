#include <unity.h>
#include "Control Tasks/BurnwireControlTask.hpp"
#include "Control Tasks/CameraControlTask.hpp"
#include "Control Tasks/RockblockControlTask.hpp"
#include "Control Tasks/VideoControlTask.hpp"
#include "MissionManager.hpp"

void test_transition_mission_modes()
{
  BurnwireControlTask burnwire_control_task(0);
  CameraControlTask camera_control_task(0);
  RockblockControlTask rockblock_control_task(0);
  VideoControlTask video_control_task(0);
  MissionManager mission_manager(0);

  sfr::mission::mode = mission_mode_type::standby;
  sfr::gps::altitude_average = 0;
  burnwire_control_task.execute();
  camera_control_task.execute();
  rockblock_control_task.execute();
  video_control_task.execute();
  mission_manager.execute();
  TEST_ASSERT_EQUAL(burnwire_mode_type::standby, sfr::burnwire::mode);
  TEST_ASSERT_EQUAL(mission_mode_type::standby, sfr::mission::mode);

  sfr::gps::altitude_average = constants::gps::high_altitude + 1;
  burnwire_control_task.execute();
  camera_control_task.execute();
  rockblock_control_task.execute();
  video_control_task.execute();
  mission_manager.execute();
  TEST_ASSERT_EQUAL(burnwire_mode_type::standby, sfr::burnwire::mode);
  TEST_ASSERT_EQUAL(mission_mode_type::high_altitude, sfr::mission::mode);
}



  int test_burnwire()
  {
    UNITY_BEGIN();

    RUN_TEST(test_transition_mission_modes);

    return UNITY_END();
  }

#ifdef DESKTOP
  int main()
  {
    return test_deployment();
  }
#else
#include <Arduino.h>
  void setup()
  {
    delay(2000);
    Serial.begin(9600);
    test_burnwire();
  }

  void loop() {}
#endif