%Timing analysis for the hash table

clc
clear all
close all

set(groot,'defaultAxesTickLabelInterpreter','latex');
hold on

filename = "HT_timing_analysis.csv"
M = readtable(filename);

plot(1:100, M.Insert)
plot(1:100, M.Search)

legend("Search", "Insert" , "interpreter", "latex")

ylabel("Time (ns)" , "interpreter", "latex")
xlabel("Iteration per 100" , "interpreter", "latex")

print -depsc hashBoth

figure
plot(1:100, M.Collisions)

xlabel("Iteration per 100" , "interpreter", "latex")
ylabel("Collisions per 100", "interpreter", "latex")

print -depsc HashCollisions



