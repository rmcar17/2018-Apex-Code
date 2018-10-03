@echo off
set input=%1
if %input% == master (
  echo Uploading to Master
  cd master
  platformio run -t upload
  cd ..
)
if %input% == slave (
  echo Uploading to Slave
  cd slave_light
  platformio run -t upload
  cd..
)
