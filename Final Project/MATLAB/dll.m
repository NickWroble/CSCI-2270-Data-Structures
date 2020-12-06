%Timing analysis for the doubly linked list

clc
clear all
close all

set(groot,'defaultAxesTickLabelInterpreter','latex');
hold on

filename = "DLL_timing_analysis.csv"
M = readtable(filename);

yyaxis left
plot(1:100, M.Insert )
ylabel("Time (ns)" , "interpreter", "latex")

yyaxis right
plot(1:100, M.Search)
ylabel("Time (ns)" , "interpreter", "latex")

legend("Insert", "Search" , "interpreter", "latex")

xlabel("Iteration per 100" , "interpreter", "latex")

print -depsc DLL



