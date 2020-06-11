close all;

%File is a tab-delimited table of simulation results
%Row 1 contains headers
%Column 1 contains time values
%Generate an example in LTspice by running a simulation
% and choosing File -> Export data as text

%Input file name
datafile = "simdata.txt";

%Get simulation data.
simfile = importdata(datafile,'\t',1);
simdata = simfile.data;

%Loop over columns of data
figure;
for n = 2:(size(simdata,2))
    subplot(size(simdata,2),1,n);   %Add a set of axes
    plot(simdata(:,1),simdata(:,n)); %Add the data
    ylabel(simfile.colheaders(n));  %Label the Y axis with the column header
end
xlabel('Time (s)'); %Label the x axis of the bottom plot