The below was the output when I attempted to run my program on the New River cluster.

eq'd    Req'd       Elap
Job ID                  Username    Queue    Jobname          SessID  NDS   TSK   Memory   Time    S   Time
----------------------- ----------- -------- ---------------- ------ ----- ------ ------ --------- - ---------
158628.master.cluster   akrinos     open_q   run_batch.sh        --      1     28    --   00:05:00 Q       -- 
nrlogin1: checkjob -v 158628
job 158628 (RM job '158628.master.cluster')

AName: run_batch.sh
State: Idle 
Creds:  user:akrinos  group:newriver  class:open_q  qos:medium_priority_qos
WallTime:   00:00:00 of 00:05:00
BecameEligible: Tue Mar 13 16:33:35
SubmitTime: Tue Mar 13 16:33:00
  (Time Queued  Total: 00:00:35  Eligible: 00:00:35)

TemplateSets:  DEFAULT
NodeMatchPolicy: EXACTNODE
Total Requested Tasks: 28
Total Requested Nodes: 1

Req[0]  TaskCount: 28  Partition: ALL
TasksPerNode: 28  NodeCount:  1


SystemID:   newriver
SystemJID:  158628
Notification Events: JobFail

UMask:          0000 
OutputFile:     nrlogin1.cluster:/home/akrinos/CMDA3634SP18Arianna/L15/run_batch.sh.o158628
ErrorFile:      nrlogin1.cluster:/home/akrinos/CMDA3634SP18Arianna/L15/run_batch.sh.e158628
Partition List: [ALL]
SrcRM:          newriver  DstRM: newriver  DstRMJID: 158628.master.cluster
Submit Args:    run_batch.sh
Flags:          RESTARTABLE
Attr:           checkpoint
StartPriority:  311
PE:             28.00
Node Availability for Partition NORMAL --------

nr049                    rejected: State (Down)
nr124                    rejected: CPU
nr147                    rejected: State (Busy)
nr155                    rejected: State (Busy)
nr156                    rejected: Class
nr001                    rejected: Class
nr002                    rejected: State (Busy)
nr003                    rejected: State (Busy)
nr004                    rejected: State (Busy)
nr005                    rejected: State (Busy)
nr006                    rejected: CPU
nr007                    rejected: State (Busy)
nr008                    rejected: CPU
nr009                    rejected: CPU
nr010                    rejected: CPU
nr011                    rejected: State (Busy)
nr012                    rejected: State (Busy)
nr013                    rejected: State (Busy)
nr014                    rejected: CPU
nr015                    rejected: State (Drained)
nr016                    rejected: State (Drained)
nr017                    rejected: State (Drained)
nr018                    rejected: State (Drained)
nr019                    rejected: Class
nr020                    rejected: Class
nr021                    rejected: Class
nr022                    rejected: Class
nr023                    rejected: Class
nr024                    rejected: Class
nr025                    rejected: Class
nr026                    rejected: Class
nr027                    rejected: State (Busy)
nr028                    rejected: Class
nr029                    rejected: CPU
nr030                    rejected: State (Busy)
nr031                    rejected: State (Busy)
nr032                    rejected: State (Busy)
nr033                    rejected: State (Busy)
nr034                    rejected: State (Busy)
nr035                    rejected: State (Busy)
nr036                    rejected: State (Busy)
nr037                    rejected: State (Busy)
nr038                    rejected: State (Busy)
nr039                    rejected: CPU
nr040                    rejected: CPU
nr041                    rejected: CPU
nr042                    rejected: CPU
nr043                    rejected: State (Busy)
nr044                    rejected: CPU
nr045                    rejected: CPU
nr046                    rejected: CPU
nr047                    rejected: CPU
nr048                    rejected: CPU
nr050                    rejected: CPU
nr051                    rejected: State (Busy)
nr052                    rejected: State (Busy)
nr053                    rejected: State (Busy)
nr054                    rejected: State (Busy)
nr055                    rejected: CPU
nr056                    rejected: State (Busy)
nr057                    rejected: CPU
nr058                    rejected: CPU
nr059                    rejected: CPU
nr060                    rejected: CPU
nr061                    rejected: State (Busy)
nr062                    rejected: CPU
nr063                    rejected: CPU
nr064                    rejected: CPU
nr065                    rejected: CPU
nr066                    rejected: CPU
nr067                    rejected: CPU
nr068                    rejected: CPU
nr069                    rejected: CPU
nr070                    rejected: State (Busy)
nr071                    rejected: CPU
nr072                    rejected: CPU
nr073                    rejected: CPU
nr074                    rejected: CPU
nr075                    rejected: CPU
nr076                    rejected: CPU
nr077                    rejected: State (Busy)
nr078                    rejected: CPU
nr079                    rejected: State (Busy)
nr080                    rejected: CPU
nr081                    rejected: CPU
nr082                    rejected: State (Busy)
nr083                    rejected: State (Busy)
nr084                    rejected: State (Busy)
nr085                    rejected: CPU
nr086                    rejected: CPU
nr087                    rejected: CPU
nr088                    rejected: CPU
nr089                    rejected: CPU
nr090                    rejected: CPU
nr091                    rejected: State (Busy)
nr092                    rejected: CPU
nr093                    rejected: CPU
nr094                    rejected: CPU
nr095                    rejected: CPU
nr096                    rejected: CPU
nr097                    rejected: CPU
nr098                    rejected: State (Down)
nr099                    rejected: CPU
nr100                    rejected: CPU
nr101                    rejected: CPU
nr102                    rejected: CPU
nr103                    rejected: State (Busy)
nr104                    rejected: CPU
nr105                    rejected: State (Busy)
nr106                    rejected: CPU
nr107                    rejected: CPU
nr108                    rejected: CPU
nr109                    rejected: CPU
nr110                    rejected: CPU
nr111                    rejected: CPU
nr112                    rejected: CPU
nr113                    rejected: State (Busy)
nr114                    rejected: State (Busy)
nr115                    rejected: State (Busy)
nr116                    rejected: CPU
nr117                    rejected: State (Busy)
nr118                    rejected: CPU
nr119                    rejected: State (Busy)
nr120                    rejected: CPU
nr121                    rejected: CPU
nr122                    rejected: CPU
nr123                    rejected: State (Busy)
nr125                    rejected: CPU
nr126                    rejected: CPU
nr127                    rejected: Class
nr128                    rejected: Class
nr129                    rejected: Class
nr130                    rejected: Class
nr131                    rejected: State (Busy)
nr132                    rejected: Class
nr133                    rejected: Class
nr134                    rejected: State (Busy)
nr135                    rejected: State (Down)
nr136                    rejected: Class
nr137                    rejected: Class
nr138                    rejected: Class
nr139                    rejected: State (Busy)
nr140                    rejected: Class
nr141                    rejected: Class
nr142                    rejected: State (Busy)
nr143                    rejected: Class
nr144                    rejected: State (Busy)
nr145                    rejected: State (Busy)
nr146                    rejected: Class
nr148                    rejected: Class
nr149                    rejected: State (Busy)
nr150                    rejected: State (Busy)
nr151                    rejected: State (Busy)
nr152                    rejected: Class
nr153                    rejected: Class
nr154                    rejected: Class
nr157                    rejected: Class
nr158                    rejected: State (Busy)
nr159                    rejected: State (Busy)
nr160                    rejected: State (Busy)
nr161                    rejected: Class
nr162                    rejected: State (Busy)
nr163                    rejected: State (Busy)
nr164                    rejected: State (Busy)
nr165                    rejected: State (Busy)
NOTE:  job req cannot run in partition NORMAL (available procs do not meet requirements : 0 of 28 procs found)
idle procs: 1461  feasible procs:   0

Node Rejection Summary: [Class: 30][CPU: 70][State: 65]

