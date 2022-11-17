#!/bin/bash
#SBATCH --nodes=1
#SBATCH --time=72:00:00
#SBATCH --job-name=test
#SBATCH --partition=itp
#SBATCH -o output_%j.txt
#SBATCH -e error_%j.txt

mkdir dummy
mv ./Test ./dummy/
cd dummy

./Test --logger=HRF,all --color_output=false --report_format=HRF --show_progress=no
