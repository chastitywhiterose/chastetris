--example script that makes a movelog for Chaste Tris
--this particular example is the SBZ Mechanical TSD
  
--begin output movelog writing 
f=io.open("imovelog.txt","wb");
  
f:write("ZAAAASSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSZASSSSSSSSSSSSSSSSSSDDDDSSSSSSSSSSSSSSSSSSSDDDDSSSSSSSSSSSSSSSSSSXXDDDDSSSSSSSSSSSSSSSSXSSSSSSSSSSSSSSSSSZAAASSSSSSSSSSSSSSSSSDDDDSSSSSSSSSSSSSSSZASSSSSSSSSSSSSSSSXXDDDDSSSSSSSSSSSSSAASSSSSSSSSSSSSSXAAAASSSSSSSSSSSSSDSXSSSSSSSSSSSSSSSZAAAASSSSSSSSSSSSSZDDSSSSSSSSSSSSSZSZSSSSSASSSSSSSSXAAASSSSSSSSSSSSSDDDDSSSSSSSSSSSSSSXXDDDDSSSSSSSSSSSSDSSSSSSSSSSSSSSDSZAAAASSSSSSSSSSSXSSSSSSSSSSSSSXSSSZSSSASSSSSSSXAASSSSSASSSSSSSDDDDSSSSSSSSSSSSSXXDDDDSSSSSSSSSSSDSSSSSSSSSSSSSDSZAAAASSSSSSSSSXSSSSSSSSSSSSXSZASSSSSSSSSSSXAAASSSSSSSSSSSDDDDSSSSSSSSSSSSXXDDDDSSSSSSSSSSSSSDSSSSSSSSSDSZAAAASSSSSSSXSSSSSSSSSSSXSZSSSASSSSSSSXAASSSSASSSSSSDDDDSSSSSSSSSSSXXDDDDSSSSSSSSSSSSDSSSSSSSSDSZAAAASSSSSXSSSSSSSSSSXSZASSSSSSSSSXAAASSSSSSSSSDDDDSSSSSSSSSSXXDDDDSSSSSSSSDSSSSSSSSSSDSZSSSSSSSSSSSSDDSSSSSXSSSSSSSSSSSSSXSZASSSSSSSSSSSSXAAASSSSSSSSSSSSDDDDSSSSSSSSSSSSSXXDDDDSSSSSSSSSSSDSSSSSSSSSSSSSDSZAAAASSSSSSSSSXSSSSSSSSSSSSXSZASSSSSSSSSSSXAAASSSSSSSSSSSSSSSSSSSSSSSSSSSSSSZDDDDDSSSSSSSSSSSXDDSSSSSSSSSSDSXDSSSSSSSSSSSSSSSSSCSSSSSDSSSSSSSSSASCZDDSSSSSSSSSSSSSZSSSSSSSSSSSSSSSSSSSSCSSSSDSSSSSSSSSSSSSSSXSSSSSSSSSSSSSSSSSSCZDDSSSSSSSSSSSSSSSSSS");

--write the movelog to a file
x=0;
while(x<1999)
do
 f:write("SSSSSSSSSSSSSSSSSSSZASSSSSSSSSSSSSSSSSSDDDDSSSSSSSSSSSSSSSSSSSDDDDSSSSSSSSSSSSSSSSSSXXDDDDSSSSSSSSSSSSSSSSXSSSSSSSSSSSSSSSSSZAAASSSSSSSSSSSSSSSSSCZAAAASSSSSSSSSSSSSSSSSZSSSASSSSSSSSSSSSSCDDDDSSSSSSSSSSSSSSSCXXDDDDSSSSSSSSSSSSSXAAASSSSSSSSSSSSSSXSSSSSSSSSSSSSSSCAASSSSSSSSSSSSSSCZAAAASSSSSSSSSSSSSZASSSSSSSSSSSXAAASSSSSSSSSSSDDDDSSSSSSSSSSSSXXDDDDSSSSSSSSSSSSSSDSSSSSSSSDSCXSSSSSSSSSSSXSZDDSSSSSSSSSSSSSZSCXSSSSDSSSSSSSSSSSSSXAAASSSSSSSSSSSSSSSSDDDDSSSSSSSSSSSSSSSSSXXDDDSDSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSDSDSZAAAASSSSSSSSSSSSSSSSSCZSSSSSSSSSSSSSSSASZASSSSSSSSSSSSSXAAASSSSSSSSSSSSSDDDDSSSSSSSSSSSSSSXXDDDDSSSSSSSSSSSSSSDSSSSSSSSSSSSDSZAAAASSSSSSSSSSSSSXSSSSSSSSSSSSSXSZASSSSSSSSSSSSXAAASSSSSSSSSSSSDDDDSSSSSSSSSSSSSXXDDDDSSSSSSSSSSSSSSDSSSSSSSSSSDSZAAAASSSSSSSSSSSXSSSSSSSSSSSSXSZASSSSSSSSSSSXAAASSSSSSSSSSSDDDDSSSSSSSSSSSSCXSSSSSSSSSSSSSSSSXSDDSSSSSSSSSSSSSSSZAAAASSSSSSSSSSSCXXDDDDSSSSSSSSSSSSZASSSSSSSSSSXAAASSSSSSSSSSDDDDSSSSSSSSSSSXXDDDDSSSSSSSSSDSSSSSSSSSSSDSZAAAASSSSSSSXSSSSSSSSSSXSCXSSSSSSSSSSSSSXSXAASSSSSASSSSSSSSSSSSSSSSSSSSSSSSSZDDDDDSSSSSSSSSSSXDDSSSSSSSSSSDSCZSSSSSSSSSSASCXDSSSSSSSSSSSSSSSSSSSSSSDSSSSSSSSSASCZDDSSSSSSSSSSSSSZSSSSSSSSSSSSSSSSSSSSCDSSSSSSSSSSSSSSSSSSSXSSSSSSSSSSSSSSSSSSCZDDSSSSSSSSSSSSSSSSSS");
 x=x+1;
 end
  
f:close();
--end movelog writing

