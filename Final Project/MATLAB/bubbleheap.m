%Timing analysis for the bubble sort and heap sort

clc
clear all
close all

set(groot,'defaultAxesTickLabelInterpreter','latex');
hold on

Bubblefilename = "Bubble_timing_analysis.csv"
Bubble = readtable(Bubblefilename);

HeapFileName = "Heap_timing_analysis.csv"
Heap = readtable(HeapFileName);



plot(1:100, Bubble.Insert)
plot(1:100, Heap.Insert)

legend("Bubble", "Heap" , "interpreter", "latex")

ylabel("Time (ns)" , "interpreter", "latex")
xlabel("Iteration per 100" , "interpreter", "latex")

print -depsc BubbleHeapInsert

figure

yyaxis left
plot(1:100, Heap.Sort)
ylabel("Time (ns)" , "interpreter", "latex")

yyaxis right
plot(1:100, Bubble.Sort)
ylabel("Time (ns)" , "interpreter", "latex")

legend("Heap", "Bubble" , "interpreter", "latex")
xlabel("Iteration per 100" , "interpreter", "latex")

print -depsc BubbleHeapSort
