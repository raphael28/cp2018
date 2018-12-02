#!/bin/sh

#PBS -l nodes=1:ppn=1:r431
#PBS -l walltime=10:00
#PBS -N a78848job

cd /home/a78848/Trabalho/

lscpu > specs.txt

rm -f a78848job*

make clean > results/erros.txt

echo "Loading modules..."

source /share/apps/intel/parallel_studio_xe_2019/compilers_and_libraries_2019/linux/bin/compilervars.sh intel64
module load gcc/4.8.2
module load papi/5.5.0
#papi_event_chooser PRESET PAPI_L1_LDM PAPI_TOT_INS

echo "Modules Loaded"

echo "Compiling source code..."

make > results/erros.txt

echo "Compilation Successful..."

for size in 5000 8000 50000 100000 500000 1000000 1500000
do
	./bin/main $size 1 5 >> results/measurements.txt
done

echo "Results in results/"
