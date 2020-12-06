%Timing analysis for the doubly linked list and hash table

clc
clear all
close all

set(groot,'defaultAxesTickLabelInterpreter','latex');
hold on

HTfilename = "HT_timing_analysis.csv"
HT = readtable(HTfilename);

DLLfilename = "DLL_timing_analysis.csv"
DLL = readtable(DLLfilename);



plot(1:100, HT.Insert)
plot(1:100, DLL.Insert)

legend("Hash", "DLL" , "interpreter", "latex")

ylabel("Time (ns)" , "interpreter", "latex")
xlabel("Iteration per 100" , "interpreter", "latex")

print -depsc HashDLLInsert

figure

yyaxis left
plot(1:100, HT.Search)
ylabel("Time (ns)" , "interpreter", "latex")

yyaxis right
plot(1:100, DLL.Search)
ylabel("Time (ns)" , "interpreter", "latex")

legend("Hash", "DLL" , "interpreter", "latex")
xlabel("Iteration per 100" , "interpreter", "latex")

print -depsc HashDLLSearch
