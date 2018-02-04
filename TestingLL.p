# number of points in moving average
n = 50

# initialize the variables
do for [i=1:n] {
    eval(sprintf("back%d=0", i))
}

# build shift function (back_n = back_n-1, ..., back1=x)
shift = "("
do for [i=n:2:-1] {
    shift = sprintf("%sback%d = back%d, ", shift, i, i-1)
} 
shift = shift."back1 = x)"
# uncomment the next line for a check
# print shift

# build sum function (back1 + ... + backn)
sum = "(back1"
do for [i=2:n] {
    sum = sprintf("%s+back%d", sum, i)
}
sum = sum.")"
# uncomment the next line for a check
# print sum

# define the functions like in the gnuplot demo
# use macro expansion for turning the strings into real functions
samples(x) = $0 > (n-1) ? n : ($0+1)
avg_n(x) = (shift_n(x), @sum/samples($0))
shift_n(x) = @shift


set terminal png

set output "TestingLL.png"

set title "The linked list bench mark"

set key right center
set key right top Right title 'Measurement' box 3

set xlabel "Linked list queue size"
    

set ylabel "Time for 50 classic holds"

set pointsize 0.5
set style func linespoints


#plot 'TestingLL.dat' using 1:2:3 w yerrorbars ls 2 title 'CI (set to 0.5 atm)', \
#'' using 1:2 w lines ls 2 notitle, \
#'' using 1:2 lt -1 pi -6 pt 7 title 'Average'

#plot 'TestingLL.dat' using 1:2 w p ls 2 title "time",\
#'' using 1:(avg_n($2)) w lines lc rgb "red" lw 3 title "average time",\

plot 'TestingLL.dat' using 1:2 lt -1 pi -6 pt 7 title  "time",\
'' using 1:2 w lines lc rgb "black" notitle,\
'' using 1:2 every 51 with points pt 7 lc rgb "red" lw 4 title "Average time",\
'' using 1:2 every 51 with linespoints lc rgb "red" lw 2 notitle


