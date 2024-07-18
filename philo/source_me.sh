# raw
x () { make -s && (set -o pipefail && _cleanup () { ret=$? ; trap - EXIT ; [ $ret = 0 ] && { < philo_output xsel --clipboard --input ; < philo_output ~/42ecole/42cursus/philosophers/philo/philosophers-visualizer/visualizer ; } ; 1>/dev/null rm -f philo_output; } && trap _cleanup EXIT && 1>/dev/null rm -f philo_output && time stdbuf -o0 ./philo "${@}" | tee philo_output ; _cleanup) || echo Cannot compile; }

# helgrind
y () { make -s && (set -o pipefail && _cleanup () { ret=$? ; trap - EXIT ; [ $ret = 0 ] && { < philo_output xsel --clipboard --input ; < philo_output ~/42ecole/42cursus/philosophers/philo/philosophers-visualizer/visualizer ; } ; 1>/dev/null rm -f philo_output; } && trap _cleanup EXIT && 1>/dev/null rm -f philo_output && time stdbuf -o0 valgrind --tool=helgrind ./philo "${@}" | tee philo_output ; _cleanup) || echo Cannot compile; }

# drd
z () { make -s && (set -o pipefail && _cleanup () { ret=$? ; trap - EXIT ; [ $ret = 0 ] && { < philo_output xsel --clipboard --input ; < philo_output ~/42ecole/42cursus/philosophers/philo/philosophers-visualizer/visualizer ; } ; 1>/dev/null rm -f philo_output; } && trap _cleanup EXIT && 1>/dev/null rm -f philo_output && time stdbuf -o0 valgrind --tool=drd ./philo "${@}" | tee philo_output ; _cleanup) || echo Cannot compile; }
