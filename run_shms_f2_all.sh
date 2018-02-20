#! /bin/bash

run_num=$1
stat_goal=$2

./hcana -q .x SCRIPTS/SHMS/PRODUCTION/replay_production_shms.C\(${run_num},-1\)

script="/net/cdaqfs/home/cdaq/hallc-online/hallc_replay/UTIL_F2_XEM/get_elecs_shms_all.C"
runbc="root -l \"${script}(${run_num}, ${stat_goal})\""
eval ${runbc}

rm elecs_shms.png
