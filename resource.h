
#include "windows.h"
#include "afxres.h"
//#include "commctrl.h"

//#pragma comment(lib,"comctl32.lib")


	// Okno g³ówne aplikacji

const int ID_B_Szuk=200;


	// Skróty klawiszowe

#define HOT_KON		10
#define HOT_ADD_A	11
#define HOT_REM_A	12
#define HOT_ED_A	13
#define HOT_P_D		14
#define	HOT_P_Z		15
#define HOT_F_W		16
#define	HOT_F_Z		17
#define	HOT_K_Z		18
#define HOT_FIR		19
#define HOT_P_T		20
#define HOT_K_A		21
#define HOT_K_K		22
#define HOT_K_I		23
#define HOT_K_U		24
#define HOT_K_S		25
#define HOT_K_D		26
#define HOT_U_WAL	27
#define HOT_U_FZ	28
#define HOT_U_ST	29
#define HOT_U_NF	30
#define HOT_U_JM	31
#define HOT_U_GR	32
#define HOT_STAT	32
	//Ikony i bitmapy


#define IDI_1				50
#define IDB_1				51
#define IDB_2				52
#define IDB_3				53
#define IDB_4				54
#define IDB_5				55

#define IDB_6				56
#define IDB_7				57
#define IDB_8				58
#define IDB_9				59
#define IDB_10				60
#define IDB_11				61
#define IDB_12				62
#define IDB_13				63
#define IDB_14				64
#define IDB_15				65
#define IDB_16				67
#define IDB_17				68

#define IDB_18				69
#define IDB_19				70
#define IDB_20				71
#define IDB_21				72
#define IDB_22				73
#define IDB_23				74
#define IDB_24				75
#define IDB_25				76
#define IDB_26				77
#define IDB_27				78
#define IDB_28				79
#define IDB_29				80
#define IDB_30				81
#define IDB_31				82
#define IDB_32				83
#define IDB_33				84
#define IDB_34				85
#define IDB_35				86
#define IDB_36				87
#define IDB_37				88
#define IDB_38				89
#define IDB_39				90
#define IDB_40				91
#define IDB_41				92
#define IDB_42				93
#define IDB_43				94
#define IDB_44				95
#define IDB_45				96
#define IDB_46				97
#define IDB_47				98
#define IDB_48				99
#define IDB_49				199
#define IDB_50				200
#define IDB_51				201
#define IDB_52				202
#define IDB_53				203
#define IDB_54				204
#define IDB_55				205
#define IDB_56				206
#define IDB_57				207
#define IDB_58				208
#define IDB_59				209
#define IDB_60				210
#define IDB_61				211
#define IDB_62				212
#define IDB_63				213
#define IDB_64				214
#define IDB_65				215
#define IDB_66				216
#define IDB_67				217
#define IDB_68				218
#define IDB_69				219
#define IDB_70				220
#define IDB_71				221
#define IDB_72				222
#define IDB_73				223
#define IDB_74				224
#define IDB_75				225
#define IDB_76				226
#define IDB_77				227

	//Identyfikatory dla menu onkna palkikacji

#define IDM					100
#define ID_Kon				101
#define	ID_Dod_A			102
#define ID_Us_A				103
#define ID_Edit_A			104
#define ID_Pr_A				105
#define ID_Za_P				106
#define ID_VAT_W			107
#define ID_VAT_Z			108
#define ID_KONT_Z			109
#define ID_FIR_P			110
#define ID_P_T				111
#define ID_K_U				112
#define ID_K_D				113
#define ID_K_Z				114
#define ID_WAL				115
#define ID_F_Z				116
#define ID_N_V				117
#define ID_VAT				118
#define ID_JM				119
#define ID_GR				120
#define ID_SZUK_KAS			121
#define ID_DEF_KAS			122
#define ID_STAT				123
#define ID_PR_MAG			124
#define ID_WART_MAG			125

// STRINGS

#define ID_S1				130


		//Okono b³êdu

#define		DLG_ERR			149
#define		DLG_ERR_T		148
#define		DLG_ERR_B		147
#define		DLG_ERR_I		146


	//Okono pytaj¹ce

#define		DLG_Q			145
#define		DLG_Q_T			144
#define		DLG_Q_B1		143
#define		DLG_Q_B2		142
#define		DLG_Q_I			141

		//Okono informacyjne

#define		DLG_I			140
#define		DLG_I_T			139
#define		DLG_I_B			138
#define		DLG_I_I			137

	// Dialog1 do dodawania artyku³ów

#define ID_DLG_1		150
#define DLG1_E1			151
#define DLG1_E2			152
#define DLG1_E3			153
#define DLG1_E4			154
#define DLG1_E5			155
#define DLG1_E6			156
#define DLG1_E7			157
#define DLG1_E8			158
#define DLG1_E9			159
#define DLG1_E10		160
#define DLG1_E11		357 
#define DLG1_E12		359 
#define DLG1_E13		362 

#define IDLG1_B1		161
#define IDLG1_B2		162
#define IDLG1_B3		163

#define DLG1_T1			164
#define DLG1_T2			165
#define DLG1_T3			166
#define DLG1_T4			167
#define DLG1_T5			168
#define DLG1_T6			169
#define DLG1_T7			170
#define DLG1_T8			171
#define DLG1_T9			172
#define DLG1_T10		173
#define DLG1_T11		356
#define DLG1_T12		358
#define DLG1_T13		363 
#define DLG1_T14		174
#define DLG1_T15		175
#define DLG1_T16		176
#define DLG1_T17		177
#define DLG1_T18		190

#define DLG1_GB1		178
#define	DLG1_GB2		179

#define DLG1_B1			180
#define DLG1_B2			181
#define DLG1_B3			182
#define DLG1_C1			183
#define DLG1_C2			184
#define DLG1_C3			185
#define	DLG1_C4			186
#define	DLG1_C5			187
#define DLG1_GB3		188
#define DLG1_E14		189
#define DLG1_E15		191

	//Okno wybierania producentów

#define ID_DLG_2		300

#define	DLG2_B1			301
#define	DLG2_B2			302
#define	DLG2_B3			303
#define	DLG2_B4			304
#define	DLG2_B5			305
#define	DLG2_B6			325	
#define DLG2_B7			326 
#define	DLG2_B8			360
#define	DLG2_B9			361 
#define	DLG2_RB1		306
#define	DLG2_RB2		307
#define	DLG2_RB3		308
#define	DLG2_RB4		309

#define	DLG2_LV1		310

#define	DLG2_E1			311
#define	DLG2_E2			312
#define	DLG2_E3			313
#define	DLG2_E4			314
#define	DLG2_E5			315
#define	DLG2_E6			316
#define	DLG2_E7			317


#define	DLG2_T1			318
#define	DLG2_T2			319
#define	DLG2_T3			320
#define	DLG2_T4			321
#define	DLG2_T5			322
#define	DLG2_T6			323
#define	DLG2_T7			324

	//Okno dialogowe dodawania dostawców

#define ID_DLG_3			325

#define	DLG3_T1			326
#define	DLG3_T2			327
#define	DLG3_T3			328
#define	DLG3_T4			329
#define	DLG3_T5			330
#define	DLG3_T6			331
#define	DLG3_T7			332
#define	DLG3_T8			333
#define	DLG3_T9			334
#define	DLG3_T10		335
#define	DLG3_T11		336
#define	DLG3_T12		337

#define	DLG3_E1			338
#define	DLG3_E2			339
#define	DLG3_E3			340
#define	DLG3_E4			341
#define	DLG3_E5			342
#define	DLG3_E6			343
#define	DLG3_E7			344
#define	DLG3_E8			345
#define	DLG3_E9			346
#define	DLG3_E10		347
#define	DLG3_E11		348
#define	DLG3_E12		349

#define	DLG3_B1			350
#define	DLG3_B2			351

#define	DLG3_RGB1		352
#define	DLG3_RGB2		353
#define	DLG3_RGB3		354

#define	DLG3_LB1		355


	//Okno dialogowe faktury VAT

#define ID_DLG_4		364

#define	DLG4_T1			365
#define	DLG4_T2			366
#define	DLG4_T3			367
#define	DLG4_T4			368
#define	DLG4_T5			369
#define	DLG4_T6			370
#define	DLG4_T7			371
#define	DLG4_T8			372
#define	DLG4_T9			373
#define	DLG4_T10		477
#define	DLG4_T11		478
#define	DLG4_T12		479		
#define	DLG4_T13		624		


#define	DLG4_E1			375
#define	DLG4_E2			376
#define	DLG4_E3			377
#define	DLG4_E4			378
#define	DLG4_E5			379
#define	DLG4_E6			380
#define	DLG4_E7			381
#define	DLG4_E8			382
#define	DLG4_E9			383
#define	DLG4_E10		474
#define	DLG4_E11		475
#define	DLG4_E12		476	
#define	DLG4_E13		625		

#define	DLG4_B1			385
#define	DLG4_B2			386
#define	DLG4_B3			387
#define	DLG4_B4			392	
#define	DLG4_B5			393	
#define	DLG4_B6			425		
#define	DLG4_B7			472	

#define DLG4_CH1		426	

#define	DLG4_RB1		388
#define	DLG4_RB2		389

#define	DLG4_LV1		390
#define	DLG4_GR1		391

	//Okno dialogowe wyboru towaru do faktury Vat


#define ID_DLG_5		394

#define	DLG5_T1			395
#define	DLG5_T2			396
#define	DLG5_T3			397

#define	DLG5_E1			398
#define	DLG5_E2			399
#define	DLG5_E3			400

#define	DLG5_B1			401
#define	DLG5_B2			402
#define	DLG5_B3			473	

#define	DLG5_LB1		403





//Okno dialogowe dodawania kontrahentów do bazy


#define ID_DLG_7		404

#define	DLG7_T1			405
#define	DLG7_T2			406
#define	DLG7_T3			407
#define	DLG7_T4			408
#define	DLG7_T5			409
#define	DLG7_T6			410
#define	DLG7_T7			411
#define	DLG7_T8			422 
#define	DLG7_T9			424 

#define	DLG7_E1			412
#define	DLG7_E2			413
#define	DLG7_E3			414
#define	DLG7_E4			415
#define	DLG7_E5			416
#define	DLG7_E6			417
#define	DLG7_E7			418
#define	DLG7_E8			419
#define	DLG7_E9			423


#define	DLG7_B1			420
#define	DLG7_B2			421


//Okno dialogowe zarz¹dzania baz¹ kontrahentów


#define ID_DLG_6		422

#define	DLG6_T1			423
#define	DLG6_T2			424
#define	DLG6_T3			425

#define	DLG6_E1			426
#define	DLG6_E2			427
#define	DLG6_E3			428

#define	DLG6_B1			429
#define	DLG6_B2			430
#define	DLG6_B3			431
#define	DLG6_B4			432
#define	DLG6_B5			433

#define	DLG6_LV1		434




//Okno dialogowe zarz¹dzania baz¹ faktur


#define ID_DLG_8		435

#define	DLG8_T1			436
#define	DLG8_T2			437
#define	DLG8_T3			438
#define	DLG8_T4			439
#define	DLG8_T5			440
#define	DLG8_T6			441
#define	DLG8_T7			442
#define	DLG8_T8			457
#define	DLG8_T9			458
#define	DLG8_T10		459	

#define	DLG8_E1			443
#define	DLG8_E2			444
#define	DLG8_E3			445
#define	DLG8_E4			446
#define	DLG8_E5			447
#define	DLG8_E6			448
#define	DLG8_E7			449
#define	DLG8_E8			450
#define	DLG8_E9			451
#define	DLG8_E10		452

#define	DLG8_B1			453
#define	DLG8_B2			454
#define	DLG8_B3			455
#define	DLG8_B4			964

#define	DLG8_LV1		456		

#define	DLG8_GB1		460
#define	DLG8_GB2		461 
#define	DLG8_GB3		462	
#define	DLG8_GB4		480

#define	DLG8_RB1		481
#define	DLG8_RB2		482 
#define	DLG8_RB3		483
#define	DLG8_RB4		484
#define	DLG8_CH1		485		


//Okno dialogowe zarz¹dzania faktur¹


#define ID_DLG_9		463

#define	DLG9_E1			464
#define	DLG9_E2			465
#define	DLG9_GB1		466
#define	DLG9_GB2		467
#define	DLG9_B1			468
#define	DLG9_B2			469
#define	DLG9_B3			470
#define	DLG9_LV1		471 

#define	DLG9_B4			965
#define	DLG9_T1			966
#define	DLG9_E3			967	




//Okno dialogowe danych firmy


#define ID_DLG_10			486	

#define	DLG10_E1			487
#define	DLG10_E2			488
#define	DLG10_E3			489
#define	DLG10_E4			490
#define	DLG10_E5			491
#define	DLG10_E6			492
#define	DLG10_E7			493
#define	DLG10_E8			494
#define	DLG10_E9			507	

#define	DLG10_T1			495
#define	DLG10_T2			496
#define	DLG10_T3			497
#define	DLG10_T4			498
#define	DLG10_T5			499
#define	DLG10_T6			500
#define	DLG10_T7			501
#define	DLG10_T8			502
#define	DLG10_T9			506		

#define	DLG10_B1			503
#define	DLG10_B2			504	



//Okno drukowania

#define ID_DLG_11			507	

#define	DLG11_CB1			508
#define	DLG11_B1			509
#define	DLG11_B2			510
#define	DLG11_RB1			511
#define	DLG11_RB2			512
#define	DLG11_RB3			513	
#define	DLG11_RB4			514
#define	DLG11_RB5			515	
#define	DLG11_GB1			516	
#define DLG11_GB2			517
#define	DLG11_RB6			518
#define	DLG11_RB7			519
#define	DLG11_RB8			520
#define DLG11_GB3			521
#define	DLG11_RB9			522
#define	DLG11_RB10			523	

#define DLG11_GB4			524		
#define DLG11_GB5			525	
#define	DLG11_RB11			526
#define	DLG11_RB12			527			



//Okno przyjêcia towaru

#define ID_DLG_12			528

#define	DLG12_E1			529
#define	DLG12_B1			530
#define	DLG12_B2			531	
#define	DLG12_T1			532
#define	DLG12_T2			533	
#define	DLG12_RB1			534
#define	DLG12_RB2			535	
#define	DLG12_CB1			536
#define	DLG12_T3			537	
#define	DLG12_E2			538	


//Okno konfiguracji kasy fiskalnej

#define ID_DLG_13			539 

#define	DLG13_T1			540
#define	DLG13_SB1			541
#define	DLG13_E1			542	
#define	DLG13_GB1			543
#define	DLG13_GB2			548 
#define	DLG13_GB3			555  
#define	DLG13_GB4			556	
#define	DLG13_RB1			544
#define	DLG13_RB2			545
#define	DLG13_RB3			546	
#define	DLG13_RB4			547 

#define	DLG13_RB5			549
#define	DLG13_RB6			550
#define	DLG13_RB7			551	
#define	DLG13_RB8			552 
#define	DLG13_RB9			553	
#define	DLG13_RB10			554 

#define	DLG13_RB11			557
#define	DLG13_RB12			558
#define	DLG13_RB13			559	
#define	DLG13_RB14			560 
#define	DLG13_RB15			561	
#define	DLG13_RB16			562 
#define	DLG13_RB17			563	
#define	DLG13_RB18			577	

#define	DLG13_T2			564
#define	DLG13_T3			565
#define	DLG13_T4			566	
#define	DLG13_T5			567 
#define	DLG13_T6			568	
#define	DLG13_T7			569 
#define	DLG13_E2			570
#define	DLG13_E3			571	
#define	DLG13_E4			572 
#define	DLG13_E5			573	
#define	DLG13_E6			574 
#define	DLG13_CB1			575	
#define	DLG13_SB2			576	
#define	DLG13_SB3			578	
#define	DLG13_SB4			579	
#define	DLG13_RB19			580	
#define	DLG13_RB20			581	
#define	DLG13_GB5			582	
#define	DLG13_T8			583
#define	DLG13_T9			584	
#define	DLG13_E7			585	
#define	DLG13_E8			586	
#define	DLG13_SB5			587	
#define	DLG13_B1			588
#define	DLG13_B2			589	
#define	DLG13_B3			590	
#define DLG13_T10			591
#define	DLG13_E9			592	
#define	DLG13_CB2			593		


//Okno zast¹pienia kasy fiskalnej

#define ID_DLG_14			594		 

#define	DLG14_LB1			595
#define	DLG14_B1			596		
#define	DLG14_B2			597		
	

//Okno zmiany ustawieñ  kasy fiskalnej

#define ID_DLG_15			598	 

#define	DLG15_LV1			599
#define	DLG15_B1			600		
#define	DLG15_B2			601		


//Okno konfiguracji walut

#define ID_DLG_16			602 

#define	DLG16_LB1			603
#define	DLG16_B1			604		
#define	DLG16_B2			605		
#define	DLG16_B3			606		
#define	DLG16_B4			607		
#define	DLG16_E1			608
#define	DLG16_E2			609	
#define	DLG16_T1			610
#define	DLG16_T2			611	
#define	DLG16_T3			612	


//Okno konfiguracji form zap³aty

#define ID_DLG_17			613

#define	DLG17_LB1			614
#define	DLG17_B1			615		
#define	DLG17_B2			616		
#define	DLG17_B3			617		
#define	DLG17_B4			618		
#define	DLG17_E1			619
#define	DLG17_E2			620
#define	DLG17_T1			621
#define	DLG17_T2			622	
#define	DLG17_T3			623	//



//Okno konfiguracji form zap³aty

#define ID_DLG_18			626

#define	DLG18_LB1			627
#define	DLG18_B1			628		
#define	DLG18_B2			629		
#define	DLG18_B3			630		
#define	DLG18_B4			631		
#define	DLG18_E1			632
#define	DLG18_E2			633
#define	DLG18_T1			634
#define	DLG18_T2			635	
#define	DLG18_T3			636 	


//Okno konfiguracji jednostek miar

#define ID_DLG_19			637 

#define	DLG19_LB1			638
#define	DLG19_B1			639		
#define	DLG19_B2			640		
#define	DLG19_B3			641		
#define	DLG19_B4			642		
#define	DLG19_E1			643
#define	DLG19_E2			644	
#define	DLG19_T1			645
#define	DLG19_T2			646	
#define	DLG19_T3			647	




//Okno konfiguracji jednostek miar

#define ID_DLG_20			648 
#define	DLG20_B1			649		
#define	DLG20_B2			650		
#define	DLG20_B3			651		
#define	DLG20_E1			652
#define	DLG20_T1			653
#define	DLG20_T2			654	
#define	DLG20_T3			655	



//Okno wyszukiwania  kasy fiskalnej

#define ID_DLG_21			656 
#define	DLG21_LV1			657
#define	DLG21_B1			658		
#define	DLG21_B2			659		
#define	DLG21_B3			660		
#define	DLG21_B4			661	
#define	DLG21_B5			662
#define	DLG21_PB1			663	
#define	DLG21_T1			664	


	//Okno zapisania wyszukanej kasy fiskalnej

#define ID_DLG_22			665	 

#define	DLG22_LV1			666
#define	DLG22_B1			667		
#define	DLG22_B2			668		
#define	DLG22_B3			669	


	//Okno zmiany domyœlnej  kasy fiskalnej

#define ID_DLG_23			670	 

#define	DLG23_LV1			671
#define	DLG23_B1			672		
#define	DLG23_B2			673	//		



	//Okno odczytywania towarów z kasy

#define ID_DLG_24			674	 

#define	DLG24_LV1			675
#define	DLG24_B1			676		
#define	DLG24_B2			677			
#define	DLG24_B3			678	
#define	DLG24_B4			679	
#define	DLG24_B5			680	
#define	DLG24_T1			681	
#define	DLG24_T2			682	
#define	DLG24_PB1			683			


	//Okno odczytywania towarów z kasy1

#define ID_DLG_25			684	 

#define	DLG25_LV1			685
#define	DLG25_B1			686		
#define	DLG25_RB1			687			
#define	DLG25_RB2			688	
#define	DLG25_RB3			689	
#define	DLG25_T1			690
#define	DLG25_PB1			691		


	//Okno odczytywania sprzeda¿y z kasy1

#define ID_DLG_26			692	 

#define	DLG26_B1			693	
#define	DLG26_B2			694	
#define	DLG26_T1			695
#define	DLG26_T2			696
#define	DLG26_PB1			697	


	//Okno odczytywania danych o towarze z kasy fiskalnej

#define ID_DLG_27			698

#define	DLG27_B1			699	
#define	DLG27_B2			700	
#define	DLG27_T1			701
#define	DLG27_T2			702
#define	DLG27_T3			703
#define	DLG27_T4			704
#define	DLG27_T5			705
#define	DLG27_T6			706
#define	DLG27_T7			707
#define	DLG27_T8			708	
#define	DLG27_E1			709
#define	DLG27_E2			710
#define	DLG27_E3			711
#define	DLG27_E4			712
#define	DLG27_E5			713
#define	DLG27_CB1			714
#define	DLG27_CB2			715
#define	DLG27_CB3			716
#define	DLG27_CB4			717
#define	DLG27_CB5			718	

#define	DLG27_LB1			719	
#define	DLG27_LB2			720
#define	DLG27_LB3			721	



	//Okno odczytywania danych o towarze z kasy fiskalnej

#define ID_DLG_28			722

#define	DLG28_B1			723	
#define	DLG28_B2			724	
#define	DLG28_B3			725
#define	DLG28_B4			726
#define	DLG28_T1			727
#define	DLG28_T2			728
#define	DLG28_T3			729
#define	DLG28_T4			730
#define	DLG28_T5			731
#define	DLG28_T6			732
#define	DLG28_E1			733
#define	DLG28_E2			734
#define	DLG28_E3			735
#define	DLG28_E4			736
#define	DLG28_E5			737		
#define	DLG28_E6			738
#define	DLG28_E7			739
#define	DLG28_E8			740	
#define	DLG28_GB1			741
#define	DLG28_GB2			742
#define	DLG28_PB1			743		
#define	DLG28_LB1			744
#define	DLG28_LB2			745		
#define	DLG28_RB1			746
#define	DLG28_RB2			747			
#define	DLG28_T7			748
#define	DLG28_T8			749
#define	DLG28_T9			750
#define	DLG28_T10			751		
#define	DLG28_T11			752		
#define	DLG28_B5			753		


//Okno konfiguracji grup towarowych

#define ID_DLG_29			754 

#define	DLG29_LB1			755
#define	DLG29_B1			756		
#define	DLG29_B2			757		
#define	DLG29_B3			758		
#define	DLG29_B4			759		
#define	DLG29_E1			760
#define	DLG29_T1			761
#define	DLG29_T2			762	


//Okno konfiguracji grup towarowych

#define ID_DLG_30			763 
#define	DLG30_T1			764
#define	DLG30_E1			765
#define	DLG30_B1			766		
#define	DLG30_B2			767		

//Okno odczytywania i zapisywania bajtów konfiguracji kasy

#define ID_DLG_31			768 
#define	DLG31_B1			769	
#define	DLG31_B2			770	
#define	DLG31_CB1			771
#define	DLG31_CB2			772
#define	DLG31_CB3			773
#define	DLG31_CB4			774
#define	DLG31_CB5			775
#define	DLG31_CB6			776
#define	DLG31_CB7			777
#define	DLG31_CB8			778
#define	DLG31_CB9			779
#define	DLG31_CB10			780
#define	DLG31_CB11			781
#define	DLG31_CB12			782
#define	DLG31_CB13			783
#define	DLG31_CB14			784
#define	DLG31_CB15			785
#define	DLG31_CB16			786
#define	DLG31_CB17			787
#define	DLG31_CB18			788
#define	DLG31_CB19			789	


//Okno konfiguracji jednostek miar w kasie

#define ID_DLG_32			790 

#define	DLG32_LB1			791
#define	DLG32_B1			792		
#define	DLG32_B2			793		
#define	DLG32_B3			794			
#define	DLG32_B4			795		
#define	DLG32_E1			796
#define	DLG32_E2			797
#define	DLG32_T1			798
#define	DLG32_T2			799 


//Okno konfiguracji grup towarowych w kasie

#define ID_DLG_33			800 

#define	DLG33_LB1			801
#define	DLG33_B1			802		
#define	DLG33_B2			803		
#define	DLG33_B3			804			
#define	DLG33_B4			805		
#define	DLG33_E1			806
#define	DLG33_E2			807
#define	DLG33_T1			808
#define	DLG33_T2			809 

//Okno konfiguracji grup towarowych w kasie

#define ID_DLG_34			810 

#define	DLG34_LB1			811
#define	DLG34_B1			812		
#define	DLG34_B2			813		


//Okno konfiguracji grup towarowych w kasie

#define ID_DLG_35			814

#define	DLG35_LB1			815
#define	DLG35_B1			816		
#define	DLG35_B2			817		
#define	DLG35_B3			818			
#define	DLG35_B4			819		
#define	DLG35_E1			820
#define	DLG35_E2			821
#define	DLG35_T1			822
#define	DLG35_T2			823		


//Okno zapisania maksymalnego rabatu

#define ID_DLG_36			824 
#define	DLG36_T1			825
#define	DLG36_E1			826
#define	DLG36_B1			827		
#define	DLG36_B2			828	

//Okno odczytania raportu godzinowego

#define ID_DLG_37			829 
#define	DLG37_LV1			830
#define	DLG37_B1			831		


//Okno konfiguracji grodzajów kasjerów w kasie

#define ID_DLG_38			832

#define	DLG38_LB1			833
#define	DLG38_B1			834		
#define	DLG38_B2			835		
#define	DLG38_B3			836				
#define	DLG38_E1			837
#define	DLG38_E2			838
#define	DLG38_E3			839
#define	DLG38_T1			840
#define	DLG38_T2			841		
#define	DLG38_T3			842		
#define	DLG38_CB1			843	
#define	DLG38_CB2			844	
#define	DLG38_CB3			845	
#define	DLG38_CB4			846	
#define	DLG38_CB5			847	
#define	DLG38_CB6			848	
#define	DLG38_CB7			849	
#define	DLG38_CB8			850	
#define	DLG38_CB9			851	
#define	DLG38_CB10			852	
#define	DLG38_CB11			853	
#define	DLG38_CB12			854	
#define	DLG38_CB13			855	
#define	DLG38_CB14			856	
#define	DLG38_CB15			857	
#define	DLG38_CB16			858		
#define	DLG38_GB1			859	
#define	DLG38_GB2			860		



	// oknio dialogowe uprawnieñ dla rodzaji kasjerów

#define ID_DLG_39			862
#define DLG39_CB1			863
#define DLG39_CB2			864
#define DLG39_CB3			865
#define DLG39_CB4			866
#define DLG39_CB5			867
#define DLG39_CB6			868
#define DLG39_CB7			869
#define DLG39_CB8			870
#define DLG39_CB9			871
#define DLG39_CB10			872
#define DLG39_CB11			873
#define DLG39_CB12			874
#define DLG39_CB13			875
#define DLG39_CB14			876
#define DLG39_CB15			877
#define DLG39_CB16			878
#define DLG39_CB17			879
#define DLG39_CB18			880
#define DLG39_CB19			881
#define DLG39_CB20			882
#define DLG39_CB21			883
#define DLG39_CB22			884
#define DLG39_CB23			885
#define DLG39_CB24			886
#define DLG39_CB25			887
#define DLG39_CB26			888
#define DLG39_CB27			889
#define DLG39_CB28			890
#define DLG39_CB29			891
#define DLG39_CB30			892
#define DLG39_CB31			893
#define DLG39_CB32			894
#define DLG39_CB33			895
#define DLG39_CB34			896
#define DLG39_CB35			897
#define DLG39_CB36			898
#define DLG39_CB37			899
#define DLG39_CB38			900
#define DLG39_CB39			901
#define DLG39_CB40			902
#define DLG39_CB41			903
#define DLG39_CB42			904
#define DLG39_CB43			905
#define DLG39_CB44			906
#define DLG39_CB45			907
#define DLG39_CB46			908
#define DLG39_CB47			909
#define DLG39_CB48			910
#define DLG39_CB49			911
#define DLG39_CB50			912
#define DLG39_CB51			913
#define DLG39_CB52			914
#define DLG39_CB53			915
#define DLG39_CB54			916
#define DLG39_CB55			917
#define DLG39_CB56			918
#define DLG39_B1			919
#define DLG39_B2			920


	// oknio dialogowe danych o kasjerach

#define ID_DLG_40			921
#define DLG40_B1			922
#define DLG40_B2			923
#define DLG40_E1			924
#define DLG40_E2			925
#define DLG40_E3			926
#define DLG40_CB1			927
#define DLG40_T1			928
#define DLG40_T2			929
#define DLG40_T3			930
#define DLG40_LB1			931		
#define DLG40_B3			932		
#define DLG40_B4			933		
#define DLG40_E4			944
#define DLG40_T4			945

	// oknio dialogowe dodania danych o kasjerach

#define ID_DLG_41			934
#define DLG41_B1			935
#define DLG41_B2			936
#define DLG41_E1			937
#define DLG41_E2			938
#define DLG41_E3			939
#define DLG41_CB1			940
#define DLG41_T1			941
#define DLG41_T2			942
#define DLG41_T3			943		
#define DLG41_E4			946		
#define DLG41_T4			947	



	// oknio dialogowe usuwania danych o kasjerach

#define ID_DLG_42			948
#define DLG42_B1			949
#define DLG42_B2			950
#define DLG42_B3			951
#define DLG42_E1			952
#define DLG42_E2			953
#define DLG42_E3			954
#define DLG42_CB1			955
#define DLG42_T1			956
#define DLG42_T2			957
#define DLG42_T3			958		
#define DLG42_E4			959		
#define DLG42_T4			960		
#define DLG42_LB1			961		
#define DLG42_LB2			962		
#define DLG42_B4			963	


	// oknio dialogowe statystyki sprzeda¿y

#define ID_DLG_43			968
#define DLG43_B1			969
#define DLG43_B2			970
#define DLG43_LV1			971
#define DLG43_LB1			972
#define DLG43_LB2			973
#define DLG43_E1			974
#define DLG43_E2			975
#define DLG43_E3			976
#define DLG43_E4			977
#define DLG43_T1			978
#define DLG43_T2			979
#define DLG43_T3			980
#define DLG43_T4			981
#define DLG43_T5			982
#define DLG43_T6			983
#define DLG43_T7			984
#define DLG43_T8			985
#define DLG43_T9			986
#define DLG43_E5			987
#define DLG43_E6			988		

	//okno dialogowe drukowania listy towarów

#define ID_DLG_44			989
#define DLG44_CB1			990
#define DLG44_B1			991
#define DLG44_B2			992
#define DLG44_GB1			993
#define DLG44_GB2			994
#define DLG44_RB1			995
#define DLG44_RB2			996
#define DLG44_RB3			997		
#define DLG44_CB2			998	

	//okno dialogowe wartoœæi towaru w magazynie

#define ID_DLG_45			999
#define DLG45_LV1			1000
#define DLG45_B1			1001	


	//okno dialogowe numeru faktury

#define ID_DLG_46			1002
#define DLG46_B1			1003
#define DLG46_B2			1004	
#define DLG46_E1			1005	//


	// kody b³êdów wiadomoœci tablicy string


#define ERR1	1001
#define ERR2	1002
#define ERR3	1003
#define ERR4	1004
#define ERR5	1005
#define ERR6	1006
#define ERR7	1007
#define ERR8	1008
#define ERR9	1009
#define ERR10	1010
#define ERR11	1011
#define ERR12	1012
#define ERR13	1013
#define ERR14	1014
#define ERR15	1015
#define ERR16	1016
#define ERR17	1017
#define ERR18	1018
#define ERR19	1019
#define ERR20	1020
#define ERR21	1021
#define ERR22	1022
#define ERR23	1023
#define ERR24	1024
#define ERR25	1025
#define ERR26	1026
#define ERR27	1027
#define ERR28	1028
#define ERR29	1029
#define ERR30	1030
#define ERR31	1031
#define ERR32	1032
#define ERR33	1033
#define ERR34	1034
#define ERR35	1035
#define ERR36	1036
#define ERR37	1037
#define ERR38	1038
#define ERR39	1039
#define ERR40	1040
#define ERR41	1041
#define ERR42	1042
#define ERR43	1043
#define ERR44	1044
#define ERR45	1045
#define ERR46	1046
#define ERR47	1047
#define ERR48	1048
#define ERR49	1049
#define ERR50	1050
#define ERR51	1051
#define ERR52	1052
#define ERR53	1053
#define ERR54	1054
#define ERR55	1055
#define ERR56	1056
#define ERR57	1057
#define ERR58	1058
#define ERR59	1059
#define ERR60	1060
#define ERR61	1061
#define ERR62	1062
#define ERR63	1063
#define ERR64	1064
#define ERR65	1065
#define ERR66	1066
#define ERR67	1067
#define ERR68	1068
#define ERR69	1069
#define ERR70	1070
#define ERR71	1071
#define ERR72	1072
#define ERR73	1073
#define ERR74	1074
#define ERR75	1075
#define ERR76	1076
#define ERR77	1077

#define ERR101	1101
#define ERR102	1102
#define ERR103	1103
#define ERR104	1104
#define ERR105	1105

#define ERR107	1107
#define ERR108	1108
#define ERR109	1109
#define ERR110	1110
#define ERR111	1111
#define ERR112	1112
#define ERR113	1113
#define ERR114	1114
#define ERR115	1115
#define ERR116	1116
#define ERR117	1117
#define ERR118	1118

#define ERR1120	1120

#define ERR1121	1122

#define ERR200	1200
#define ERR201	1201
#define ERR202	1202
#define ERR203	1203
#define ERR204	1204
#define ERR205	1205
#define ERR206	1206
#define ERR207	1207
#define ERR208	1208
#define ERR209	1209
#define ERR210	1210
#define ERR211	1211
#define ERR212	1212
#define ERR213	1213

#define ERR215	1215

#define ERR217	1217

#define ERR220	1220
#define ERR221	1221
#define ERR222	1222
#define ERR223	1223
#define ERR224	1224
#define ERR225	1225
#define ERR226	1226
#define ERR227	1227
#define ERR228	1228
#define ERR229	1229
#define ERR230	1230
#define ERR231	1231
#define ERR232	1232

#define ERR234	1234
#define ERR235	1235
#define ERR236	1236
#define ERR237	1237
#define ERR238	1238
#define ERR239	1239
#define ERR240	1240
#define ERR241	1241
#define ERR242	1242

// bledy rozszerzone 6CXX (wiadomosci kasjerskie)


#define ERR6C01		0x6C01
#define ERR6C02		0x6C02
#define ERR6C03		0x6C03
#define ERR6C04		0x6C04
#define ERR6C05		0x6C05
#define ERR6C06		0x6C06
#define ERR6C07		0x6C07
#define ERR6C08		0x6C08
#define ERR6C09		0x6C09
#define ERR6C0A		0x6C0A
#define ERR6C0B		0x6C0B
#define ERR6C0C		0x6C0C


//bledy rozszerzone D4XX (rabaty/narzuty automatyczne)


#define ERR6D01		0x6D01
#define ERR6D02		0x6D02
#define ERR6D03		0x6D03
#define ERR6D04		0x6D04
#define ERR6D05		0x6D05
#define ERR6D06		0x6D06
#define ERR6D07		0x6D07
#define ERR6D08		0x6D08
#define ERR6D09		0x6D09
#define ERR6D0A		0x6D0A
#define ERR6D0B		0x6D0B
#define ERR6D0C		0x6D0C
#define ERR6D0D		0x6D0D
#define ERR6D0E		0x6D0E

