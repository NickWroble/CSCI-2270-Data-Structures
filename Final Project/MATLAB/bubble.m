%Timing analysis for bubble sort

clc
clear all
close all

set(groot,'defaultAxesTickLabelInterpreter','latex');
hold on

filename = "Bubble_timing_analysis.csv"
M = readtable(filename);

yyaxis left
plot(1:100, M.Insert )
ylabel("Time (ns)" , "interpreter", "latex")

yyaxis right
plot(1:100, M.Sort)
ylabel("Time (ns)" , "interpreter", "latex")

legend("Insert", "Sort" , "interpreter", "latex")

xlabel("Iteration per 100" , "interpreter", "latex")


print -depsc Bubble


