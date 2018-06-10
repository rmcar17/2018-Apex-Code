@echo off
set input=%1
if %input% == master (
  echo Uploading to Master
  cd master
  pio run -t upload
  cd ..
)
if %input% == slave (
  echo Uploading to Slave
  cd slave_light
  pio run -t upload
  cd..
)
