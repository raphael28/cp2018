#!/bin/sh

#PBS -l nodes=1:ppn=24:r431
#PBS -l walltime=10:00
#PBS -N a79821job

cd /home/a79821/Trabalho/

lscpu > specs.txt

rm -f a79821job*

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

for size in 100 1000 10000 1000000
do	
	for nB in 16 32 64 128
	do
		for nThreads in 1 2 4
		do
		export OMP_NUM_THREADS=$nThreads
		./bin/main $size $nB $nThreads 5 >> results/measurements.txt
		done
	done
done

echo "Results in results/"
