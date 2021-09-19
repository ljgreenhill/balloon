#include <unity.h>
#include "Control Tasks/BurnwireControlTask.hpp"
#include "Control Tasks/CameraControlTask.hpp"
#include "Control Tasks/RockblockControlTask.hpp"
#include "Control Tasks/VideoControlTask.hpp"
#include "Monitors/CommandMonitor.hpp"
#include "MissionManager.hpp"

void test_timeout_max_attempts()
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

  sfr::gps::altitude_average = 0;
  sfr::timer::start_time = -constants::timer::fail_safe_deploy;
  burnwire_control_task.execute();
  camera_control_task.execute();
  rockblock_control_task.execute();
  video_control_task.execute();
  mission_manager.execute();
  TEST_ASSERT_EQUAL(burnwire_mode_type::standby, sfr::burnwire::mode);
  TEST_ASSERT_EQUAL(mission_mode_type::deployment, sfr::mission::mode);

  burnwire_control_task.execute();
  camera_control_task.execute();
  rockblock_control_task.execute();
  video_control_task.execute();
  mission_manager.execute();
  TEST_ASSERT_EQUAL(burnwire_mode_type::burn, sfr::burnwire::mode);
  TEST_ASSERT_EQUAL(mission_mode_type::deployment, sfr::mission::mode);

  for(int i=0; i <constants::burnwire::max_attempts; ++i){
    delay(sfr::burnwire::burn_time);
    burnwire_control_task.execute();
    camera_control_task.execute();
    rockblock_control_task.execute();
    video_control_task.execute();
    mission_manager.execute();
    TEST_ASSERT_EQUAL(burnwire_mode_type::delay, sfr::burnwire::mode);

    delay(constants::burnwire::burn_wait);
    burnwire_control_task.execute();
    camera_control_task.execute();
    rockblock_control_task.execute();
    video_control_task.execute();
    mission_manager.execute();
    TEST_ASSERT_EQUAL(burnwire_mode_type::burn, sfr::burnwire::mode);
  }

  burnwire_control_task.execute();
  camera_control_task.execute();
  rockblock_control_task.execute();
  video_control_task.execute();
  mission_manager.execute();
  TEST_ASSERT_EQUAL(burnwire_mode_type::standby, sfr::burnwire::mode);
  TEST_ASSERT_EQUAL(mission_mode_type::post_deployment, sfr::mission::mode);
}

void test_timeout_photoresistor()
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

  sfr::gps::altitude_average = 0;
  sfr::timer::start_time = -constants::timer::fail_safe_deploy;
  burnwire_control_task.execute();
  camera_control_task.execute();
  rockblock_control_task.execute();
  video_control_task.execute();
  mission_manager.execute();
  TEST_ASSERT_EQUAL(burnwire_mode_type::standby, sfr::burnwire::mode);
  TEST_ASSERT_EQUAL(mission_mode_type::deployment, sfr::mission::mode);

  burnwire_control_task.execute();
  camera_control_task.execute();
  rockblock_control_task.execute();
  video_control_task.execute();
  mission_manager.execute();
  TEST_ASSERT_EQUAL(burnwire_mode_type::burn, sfr::burnwire::mode);
  TEST_ASSERT_EQUAL(mission_mode_type::deployment, sfr::mission::mode);

  sfr::photoresistor::covered = false;

  burnwire_control_task.execute();
  camera_control_task.execute();
  rockblock_control_task.execute();
  video_control_task.execute();
  mission_manager.execute();
  TEST_ASSERT_EQUAL(burnwire_mode_type::standby, sfr::burnwire::mode);
  TEST_ASSERT_EQUAL(mission_mode_type::post_deployment, sfr::mission::mode);
}

void test_gps()
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

  sfr::gps::altitude_average = constants::gps::mand_deploy + 1;
  burnwire_control_task.execute();
  camera_control_task.execute();
  rockblock_control_task.execute();
  video_control_task.execute();
  mission_manager.execute();
  TEST_ASSERT_EQUAL(burnwire_mode_type::standby, sfr::burnwire::mode);
  TEST_ASSERT_EQUAL(mission_mode_type::deployment, sfr::mission::mode);

  sfr::photoresistor::covered = true;
  burnwire_control_task.execute();
  camera_control_task.execute();
  rockblock_control_task.execute();
  video_control_task.execute();
  mission_manager.execute();
  TEST_ASSERT_EQUAL(burnwire_mode_type::burn, sfr::burnwire::mode);
  TEST_ASSERT_EQUAL(mission_mode_type::deployment, sfr::mission::mode);

  for(int i=0; i <constants::burnwire::max_attempts; ++i){
    delay(sfr::burnwire::burn_time);
    burnwire_control_task.execute();
    camera_control_task.execute();
    rockblock_control_task.execute();
    video_control_task.execute();
    mission_manager.execute();
    TEST_ASSERT_EQUAL(burnwire_mode_type::delay, sfr::burnwire::mode);

    delay(constants::burnwire::burn_wait);
    burnwire_control_task.execute();
    camera_control_task.execute();
    rockblock_control_task.execute();
    video_control_task.execute();
    mission_manager.execute();
    TEST_ASSERT_EQUAL(burnwire_mode_type::burn, sfr::burnwire::mode);
  }

  burnwire_control_task.execute();
  camera_control_task.execute();
  rockblock_control_task.execute();
  video_control_task.execute();
  mission_manager.execute();
  TEST_ASSERT_EQUAL(burnwire_mode_type::standby, sfr::burnwire::mode);
  TEST_ASSERT_EQUAL(mission_mode_type::post_deployment, sfr::mission::mode);
}

void test_rockblock()
{
  BurnwireControlTask burnwire_control_task(0);
  CameraControlTask camera_control_task(0);
  RockblockControlTask rockblock_control_task(0);
  VideoControlTask video_control_task(0);
  MissionManager mission_manager(0);
  CommandMonitor command_monitor(0);
  RockblockSimulator sim;

  sim.begin(constants::rockblock::baud);

  sfr::mission::mode = mission_mode_type::standby;
  sfr::gps::altitude_average = 0;
  burnwire_control_task.execute();
  camera_control_task.execute();
  rockblock_control_task.execute();
  video_control_task.execute();
  mission_manager.execute();
  TEST_ASSERT_EQUAL(burnwire_mode_type::standby, sfr::burnwire::mode);
  TEST_ASSERT_EQUAL(mission_mode_type::standby, sfr::mission::mode);
  
  sim.insert("00000200000000000000");
  sfr::rockblock::downlink_period = 0;
  while(!sfr::rockblock::waiting_command){
    burnwire_control_task.execute();
    camera_control_task.execute();
    rockblock_control_task.execute();
    video_control_task.execute();
    command_monitor.execute();
    mission_manager.execute();
  }
  
  TEST_ASSERT_EQUAL(burnwire_mode_type::standby, sfr::burnwire::mode);
  TEST_ASSERT_EQUAL(mission_mode_type::deployment, sfr::mission::mode);

  sfr::photoresistor::covered = true;
  burnwire_control_task.execute();
  camera_control_task.execute();
  rockblock_control_task.execute();
  video_control_task.execute();
  mission_manager.execute();
  TEST_ASSERT_EQUAL(burnwire_mode_type::burn, sfr::burnwire::mode);
  TEST_ASSERT_EQUAL(mission_mode_type::deployment, sfr::mission::mode);

  for(int i=0; i <constants::burnwire::max_attempts; ++i){
    delay(sfr::burnwire::burn_time);
    burnwire_control_task.execute();
    camera_control_task.execute();
    rockblock_control_task.execute();
    video_control_task.execute();
    mission_manager.execute();
    TEST_ASSERT_EQUAL(burnwire_mode_type::delay, sfr::burnwire::mode);

    delay(constants::burnwire::burn_wait);
    burnwire_control_task.execute();
    camera_control_task.execute();
    rockblock_control_task.execute();
    video_control_task.execute();
    mission_manager.execute();
    TEST_ASSERT_EQUAL(burnwire_mode_type::burn, sfr::burnwire::mode);
  }

  burnwire_control_task.execute();
  camera_control_task.execute();
  rockblock_control_task.execute();
  video_control_task.execute();
  mission_manager.execute();
  TEST_ASSERT_EQUAL(burnwire_mode_type::standby, sfr::burnwire::mode);
  TEST_ASSERT_EQUAL(mission_mode_type::post_deployment, sfr::mission::mode);
}

  int test_burnwire()
  {
    UNITY_BEGIN();

    RUN_TEST(test_timeout_max_attempts);
    RUN_TEST(test_timeout_photoresistor);
    RUN_TEST(test_gps);
    //RUN_TEST(test_rockblock);

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