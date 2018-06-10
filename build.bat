@echo off
set input=%1
if %input% == master (
  echo Building Master
  cd master
  pio run
  cd ..
)
if %input% == slave (
  echo Building Slave
  cd slave_light
  pio run
  cd..
)
