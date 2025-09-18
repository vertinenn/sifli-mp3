
build_sf32lb52-lchspi-ulp_hcpu\lcpu\lcpu.elf:     file format elf32-littlearm


Disassembly of section .text:

00400000 <__Vectors>:
  400000:	204019f0 	.word	0x204019f0
  400004:	0040027d 	.word	0x0040027d
  400008:	0040035d 	.word	0x0040035d
  40000c:	000008a9 	.word	0x000008a9
  400010:	000008e5 	.word	0x000008e5
  400014:	004002c7 	.word	0x004002c7
  400018:	004002c7 	.word	0x004002c7
  40001c:	004002c7 	.word	0x004002c7
	...
  40002c:	004002c7 	.word	0x004002c7
  400030:	004002c7 	.word	0x004002c7
  400034:	00000000 	.word	0x00000000
  400038:	0000080d 	.word	0x0000080d
  40003c:	00400e8d 	.word	0x00400e8d
  400040:	00400db9 	.word	0x00400db9
  400044:	00004fa1 	.word	0x00004fa1
  400048:	004002c7 	.word	0x004002c7
  40004c:	004002c7 	.word	0x004002c7
  400050:	004002c7 	.word	0x004002c7
  400054:	004002c7 	.word	0x004002c7
  400058:	004002c7 	.word	0x004002c7
  40005c:	004002c7 	.word	0x004002c7
  400060:	004002c7 	.word	0x004002c7
  400064:	004002c7 	.word	0x004002c7
  400068:	004002c7 	.word	0x004002c7
  40006c:	00007361 	.word	0x00007361
  400070:	004002c7 	.word	0x004002c7
  400074:	004002c7 	.word	0x004002c7
  400078:	004002c7 	.word	0x004002c7
  40007c:	00005901 	.word	0x00005901
  400080:	004002c7 	.word	0x004002c7
  400084:	004002c7 	.word	0x004002c7
  400088:	00400a59 	.word	0x00400a59
  40008c:	004002c7 	.word	0x004002c7
  400090:	004002c7 	.word	0x004002c7
  400094:	004002c7 	.word	0x004002c7
  400098:	004002c7 	.word	0x004002c7
  40009c:	00400b51 	.word	0x00400b51
  4000a0:	004002c7 	.word	0x004002c7
  4000a4:	004002c7 	.word	0x004002c7
  4000a8:	004002c7 	.word	0x004002c7
  4000ac:	004002c7 	.word	0x004002c7
  4000b0:	004002c7 	.word	0x004002c7
  4000b4:	004002c7 	.word	0x004002c7
  4000b8:	004002c7 	.word	0x004002c7
  4000bc:	004002c7 	.word	0x004002c7
	...

00400100 <deregister_tm_clones>:
  400100:	4803      	ldr	r0, [pc, #12]	@ (400110 <deregister_tm_clones+0x10>)
  400102:	4b04      	ldr	r3, [pc, #16]	@ (400114 <deregister_tm_clones+0x14>)
  400104:	4283      	cmp	r3, r0
  400106:	d002      	beq.n	40010e <deregister_tm_clones+0xe>
  400108:	4b03      	ldr	r3, [pc, #12]	@ (400118 <deregister_tm_clones+0x18>)
  40010a:	b103      	cbz	r3, 40010e <deregister_tm_clones+0xe>
  40010c:	4718      	bx	r3
  40010e:	4770      	bx	lr
  400110:	204015ec 	.word	0x204015ec
  400114:	204015ec 	.word	0x204015ec
  400118:	00000000 	.word	0x00000000

0040011c <register_tm_clones>:
  40011c:	4b06      	ldr	r3, [pc, #24]	@ (400138 <register_tm_clones+0x1c>)
  40011e:	4907      	ldr	r1, [pc, #28]	@ (40013c <register_tm_clones+0x20>)
  400120:	1ac9      	subs	r1, r1, r3
  400122:	1089      	asrs	r1, r1, #2
  400124:	bf48      	it	mi
  400126:	3101      	addmi	r1, #1
  400128:	1049      	asrs	r1, r1, #1
  40012a:	d003      	beq.n	400134 <register_tm_clones+0x18>
  40012c:	4b04      	ldr	r3, [pc, #16]	@ (400140 <register_tm_clones+0x24>)
  40012e:	b10b      	cbz	r3, 400134 <register_tm_clones+0x18>
  400130:	4801      	ldr	r0, [pc, #4]	@ (400138 <register_tm_clones+0x1c>)
  400132:	4718      	bx	r3
  400134:	4770      	bx	lr
  400136:	bf00      	nop
  400138:	204015ec 	.word	0x204015ec
  40013c:	204015ec 	.word	0x204015ec
  400140:	00000000 	.word	0x00000000

00400144 <__do_global_dtors_aux>:
  400144:	b510      	push	{r4, lr}
  400146:	4c06      	ldr	r4, [pc, #24]	@ (400160 <__do_global_dtors_aux+0x1c>)
  400148:	7823      	ldrb	r3, [r4, #0]
  40014a:	b943      	cbnz	r3, 40015e <__do_global_dtors_aux+0x1a>
  40014c:	f7ff ffd8 	bl	400100 <deregister_tm_clones>
  400150:	4b04      	ldr	r3, [pc, #16]	@ (400164 <__do_global_dtors_aux+0x20>)
  400152:	b113      	cbz	r3, 40015a <__do_global_dtors_aux+0x16>
  400154:	4804      	ldr	r0, [pc, #16]	@ (400168 <__do_global_dtors_aux+0x24>)
  400156:	f3af 8000 	nop.w
  40015a:	2301      	movs	r3, #1
  40015c:	7023      	strb	r3, [r4, #0]
  40015e:	bd10      	pop	{r4, pc}
  400160:	204019f0 	.word	0x204019f0
  400164:	00000000 	.word	0x00000000
  400168:	00401594 	.word	0x00401594

0040016c <frame_dummy>:
  40016c:	b508      	push	{r3, lr}
  40016e:	4b05      	ldr	r3, [pc, #20]	@ (400184 <frame_dummy+0x18>)
  400170:	b11b      	cbz	r3, 40017a <frame_dummy+0xe>
  400172:	4905      	ldr	r1, [pc, #20]	@ (400188 <frame_dummy+0x1c>)
  400174:	4805      	ldr	r0, [pc, #20]	@ (40018c <frame_dummy+0x20>)
  400176:	f3af 8000 	nop.w
  40017a:	e8bd 4008 	ldmia.w	sp!, {r3, lr}
  40017e:	f7ff bfcd 	b.w	40011c <register_tm_clones>
  400182:	bf00      	nop
  400184:	00000000 	.word	0x00000000
  400188:	204019f4 	.word	0x204019f4
  40018c:	00401594 	.word	0x00401594

00400190 <HAL_MspInit>:
  400190:	4770      	bx	lr

00400192 <SystemClock_Config>:
  400192:	4770      	bx	lr

00400194 <rc10k_cal_hook_func>:
  400194:	b537      	push	{r0, r1, r2, r4, r5, lr}
  400196:	f640 32b8 	movw	r2, #3000	@ 0xbb8
  40019a:	4b08      	ldr	r3, [pc, #32]	@ (4001bc <rc10k_cal_hook_func+0x28>)
  40019c:	4c08      	ldr	r4, [pc, #32]	@ (4001c0 <rc10k_cal_hook_func+0x2c>)
  40019e:	6c9d      	ldr	r5, [r3, #72]	@ 0x48
  4001a0:	6823      	ldr	r3, [r4, #0]
  4001a2:	1aeb      	subs	r3, r5, r3
  4001a4:	4293      	cmp	r3, r2
  4001a6:	d906      	bls.n	4001b6 <rc10k_cal_hook_func+0x22>
  4001a8:	f000 f92a 	bl	400400 <HAL_RC_CAL_GetLPCycle_ex>
  4001ac:	a901      	add	r1, sp, #4
  4001ae:	f000 f937 	bl	400420 <HAL_RC_CALget_curr_cycle_on_48M>
  4001b2:	b900      	cbnz	r0, 4001b6 <rc10k_cal_hook_func+0x22>
  4001b4:	6025      	str	r5, [r4, #0]
  4001b6:	b003      	add	sp, #12
  4001b8:	bd30      	pop	{r4, r5, pc}
  4001ba:	bf00      	nop
  4001bc:	40040000 	.word	0x40040000
  4001c0:	20401a0c 	.word	0x20401a0c

004001c4 <rc10k_cal_init>:
  4001c4:	b507      	push	{r0, r1, r2, lr}
  4001c6:	4b0b      	ldr	r3, [pc, #44]	@ (4001f4 <rc10k_cal_init+0x30>)
  4001c8:	f893 30db 	ldrb.w	r3, [r3, #219]	@ 0xdb
  4001cc:	b173      	cbz	r3, 4001ec <rc10k_cal_init+0x28>
  4001ce:	4b0a      	ldr	r3, [pc, #40]	@ (4001f8 <rc10k_cal_init+0x34>)
  4001d0:	480a      	ldr	r0, [pc, #40]	@ (4001fc <rc10k_cal_init+0x38>)
  4001d2:	6c9a      	ldr	r2, [r3, #72]	@ 0x48
  4001d4:	4b0a      	ldr	r3, [pc, #40]	@ (400200 <rc10k_cal_init+0x3c>)
  4001d6:	601a      	str	r2, [r3, #0]
  4001d8:	f455 fd92 	bl	55d00 <rt_thread_idle_sethook>
  4001dc:	2014      	movs	r0, #20
  4001de:	f000 f915 	bl	40040c <HAL_RC_CAL_SetLPCycle_ex>
  4001e2:	f000 f90d 	bl	400400 <HAL_RC_CAL_GetLPCycle_ex>
  4001e6:	a901      	add	r1, sp, #4
  4001e8:	f000 f91a 	bl	400420 <HAL_RC_CALget_curr_cycle_on_48M>
  4001ec:	2000      	movs	r0, #0
  4001ee:	b003      	add	sp, #12
  4001f0:	f85d fb04 	ldr.w	pc, [sp], #4
  4001f4:	2040fd00 	.word	0x2040fd00
  4001f8:	40040000 	.word	0x40040000
  4001fc:	00400195 	.word	0x00400195
  400200:	20401a0c 	.word	0x20401a0c

00400204 <main>:
  400204:	2000      	movs	r0, #0
  400206:	4770      	bx	lr

00400208 <HAL_PreInit>:
  400208:	b508      	push	{r3, lr}
  40020a:	f401 fed1 	bl	1fb0 <HAL_LPAON_EnableXT48>
  40020e:	f04f 4280 	mov.w	r2, #1073741824	@ 0x40000000
  400212:	6913      	ldr	r3, [r2, #16]
  400214:	2101      	movs	r1, #1
  400216:	f023 0303 	bic.w	r3, r3, #3
  40021a:	f043 0301 	orr.w	r3, r3, #1
  40021e:	6113      	str	r3, [r2, #16]
  400220:	6913      	ldr	r3, [r2, #16]
  400222:	2002      	movs	r0, #2
  400224:	f043 0310 	orr.w	r3, r3, #16
  400228:	6113      	str	r3, [r2, #16]
  40022a:	2203      	movs	r2, #3
  40022c:	f402 f88c 	bl	2348 <HAL_RCC_LCPU_SetDiv>
  400230:	e8bd 4008 	ldmia.w	sp!, {r3, lr}
  400234:	f7ff bfac 	b.w	400190 <HAL_MspInit>

00400238 <hw_preinit0>:
  400238:	4770      	bx	lr
	...

0040023c <SystemInit>:
  40023c:	b508      	push	{r3, lr}
  40023e:	4a0b      	ldr	r2, [pc, #44]	@ (40026c <SystemInit+0x30>)
  400240:	4b0b      	ldr	r3, [pc, #44]	@ (400270 <SystemInit+0x34>)
  400242:	609a      	str	r2, [r3, #8]
  400244:	f8d3 2088 	ldr.w	r2, [r3, #136]	@ 0x88
  400248:	f042 023f 	orr.w	r2, r2, #63	@ 0x3f
  40024c:	f8c3 2088 	str.w	r2, [r3, #136]	@ 0x88
  400250:	f7ff fff2 	bl	400238 <hw_preinit0>
  400254:	f450 f9ba 	bl	505cc <mpu_config>
  400258:	f405 fe76 	bl	5f48 <cache_enable>
  40025c:	f000 fce7 	bl	400c2e <SystemPowerOnModeInit>
  400260:	f451 f836 	bl	512d0 <rom_scatterload>
  400264:	4b03      	ldr	r3, [pc, #12]	@ (400274 <SystemInit+0x38>)
  400266:	4a04      	ldr	r2, [pc, #16]	@ (400278 <SystemInit+0x3c>)
  400268:	601a      	str	r2, [r3, #0]
  40026a:	bd08      	pop	{r3, pc}
  40026c:	00400000 	.word	0x00400000
  400270:	e000ed00 	.word	0xe000ed00
  400274:	204015b0 	.word	0x204015b0
  400278:	017d7840 	.word	0x017d7840

0040027c <Reset_Handler>:
  40027c:	f8df d048 	ldr.w	sp, [pc, #72]	@ 4002c8 <BTIM3_IRQHandler+0x2>
  400280:	4812      	ldr	r0, [pc, #72]	@ (4002cc <BTIM3_IRQHandler+0x6>)
  400282:	f380 880a 	msr	MSPLIM, r0
  400286:	f7ff ffd9 	bl	40023c <SystemInit>
  40028a:	4c11      	ldr	r4, [pc, #68]	@ (4002d0 <BTIM3_IRQHandler+0xa>)
  40028c:	4d11      	ldr	r5, [pc, #68]	@ (4002d4 <BTIM3_IRQHandler+0xe>)
  40028e:	42ac      	cmp	r4, r5
  400290:	da09      	bge.n	4002a6 <Reset_Handler+0x2a>
  400292:	6821      	ldr	r1, [r4, #0]
  400294:	6862      	ldr	r2, [r4, #4]
  400296:	68a3      	ldr	r3, [r4, #8]
  400298:	3b04      	subs	r3, #4
  40029a:	bfa2      	ittt	ge
  40029c:	58c8      	ldrge	r0, [r1, r3]
  40029e:	50d0      	strge	r0, [r2, r3]
  4002a0:	e7fa      	bge.n	400298 <Reset_Handler+0x1c>
  4002a2:	340c      	adds	r4, #12
  4002a4:	e7f3      	b.n	40028e <Reset_Handler+0x12>
  4002a6:	4b0c      	ldr	r3, [pc, #48]	@ (4002d8 <BTIM3_IRQHandler+0x12>)
  4002a8:	4c0c      	ldr	r4, [pc, #48]	@ (4002dc <BTIM3_IRQHandler+0x16>)
  4002aa:	42a3      	cmp	r3, r4
  4002ac:	da08      	bge.n	4002c0 <Reset_Handler+0x44>
  4002ae:	6819      	ldr	r1, [r3, #0]
  4002b0:	685a      	ldr	r2, [r3, #4]
  4002b2:	2000      	movs	r0, #0
  4002b4:	3a04      	subs	r2, #4
  4002b6:	bfa4      	itt	ge
  4002b8:	5088      	strge	r0, [r1, r2]
  4002ba:	e7fb      	bge.n	4002b4 <Reset_Handler+0x38>
  4002bc:	3308      	adds	r3, #8
  4002be:	e7f4      	b.n	4002aa <Reset_Handler+0x2e>
  4002c0:	f000 fec4 	bl	40104c <entry>
  4002c4:	e7fe      	b.n	4002c4 <Reset_Handler+0x48>

004002c6 <BTIM3_IRQHandler>:
  4002c6:	e7fe      	b.n	4002c6 <BTIM3_IRQHandler>
  4002c8:	204019f0 	.word	0x204019f0
  4002cc:	204015f0 	.word	0x204015f0
  4002d0:	004015a8 	.word	0x004015a8
  4002d4:	004015a8 	.word	0x004015a8
  4002d8:	004015a8 	.word	0x004015a8
  4002dc:	004015b0 	.word	0x004015b0

004002e0 <__aeabi_unwind_cpp_pr0>:
  4002e0:	2000      	movs	r0, #0
  4002e2:	4770      	bx	lr

004002e4 <HAL_PostMspInit>:
  4002e4:	4770      	bx	lr

004002e6 <HAL_Init>:
  4002e6:	b508      	push	{r3, lr}
  4002e8:	f7ff ff8e 	bl	400208 <HAL_PreInit>
  4002ec:	f7ff fffa 	bl	4002e4 <HAL_PostMspInit>
  4002f0:	f000 fa61 	bl	4007b6 <HAL_RCC_Init>
  4002f4:	2003      	movs	r0, #3
  4002f6:	f401 fefb 	bl	20f0 <HAL_NVIC_SetPriorityGrouping>
  4002fa:	2000      	movs	r0, #0
  4002fc:	f000 fdc3 	bl	400e86 <HAL_InitTick>
  400300:	3800      	subs	r0, #0
  400302:	bf18      	it	ne
  400304:	2001      	movne	r0, #1
  400306:	bd08      	pop	{r3, pc}

00400308 <HAL_IncTick>:
  400308:	4a02      	ldr	r2, [pc, #8]	@ (400314 <HAL_IncTick+0xc>)
  40030a:	6813      	ldr	r3, [r2, #0]
  40030c:	3301      	adds	r3, #1
  40030e:	6013      	str	r3, [r2, #0]
  400310:	4770      	bx	lr
  400312:	bf00      	nop
  400314:	20401a10 	.word	0x20401a10

00400318 <HAL_Delay_us>:
  400318:	4603      	mov	r3, r0
  40031a:	b570      	push	{r4, r5, r6, lr}
  40031c:	b1b8      	cbz	r0, 40034e <HAL_Delay_us+0x36>
  40031e:	f242 7510 	movw	r5, #10000	@ 0x2710
  400322:	f04f 26e0 	mov.w	r6, #3758153728	@ 0xe000e000
  400326:	42ab      	cmp	r3, r5
  400328:	bf84      	itt	hi
  40032a:	f5a3 541c 	subhi.w	r4, r3, #9984	@ 0x2700
  40032e:	f242 7310 	movwhi	r3, #10000	@ 0x2710
  400332:	6932      	ldr	r2, [r6, #16]
  400334:	bf98      	it	ls
  400336:	2400      	movls	r4, #0
  400338:	4618      	mov	r0, r3
  40033a:	bf88      	it	hi
  40033c:	3c10      	subhi	r4, #16
  40033e:	07d3      	lsls	r3, r2, #31
  400340:	d408      	bmi.n	400354 <HAL_Delay_us+0x3c>
  400342:	f401 fcc3 	bl	1ccc <HAL_Delay_us_>
  400346:	4623      	mov	r3, r4
  400348:	2c00      	cmp	r4, #0
  40034a:	d1ec      	bne.n	400326 <HAL_Delay_us+0xe>
  40034c:	e001      	b.n	400352 <HAL_Delay_us+0x3a>
  40034e:	f401 fcbd 	bl	1ccc <HAL_Delay_us_>
  400352:	bd70      	pop	{r4, r5, r6, pc}
  400354:	f401 fc9c 	bl	1c90 <HAL_Delay_us2_>
  400358:	e7f5      	b.n	400346 <HAL_Delay_us+0x2e>
	...

0040035c <NMI_Handler>:
  40035c:	b508      	push	{r3, lr}
  40035e:	4b05      	ldr	r3, [pc, #20]	@ (400374 <NMI_Handler+0x18>)
  400360:	691b      	ldr	r3, [r3, #16]
  400362:	005b      	lsls	r3, r3, #1
  400364:	d502      	bpl.n	40036c <NMI_Handler+0x10>
  400366:	f000 fc37 	bl	400bd8 <DBG_Trigger_IRQHandler>
  40036a:	bd08      	pop	{r3, pc}
  40036c:	f000 fd2e 	bl	400dcc <WDT_IRQHandler>
  400370:	e7fb      	b.n	40036a <NMI_Handler+0xe>
  400372:	bf00      	nop
  400374:	4000f000 	.word	0x4000f000

00400378 <HAL_GPIO_Restore>:
  400378:	4b11      	ldr	r3, [pc, #68]	@ (4003c0 <HAL_GPIO_Restore+0x48>)
  40037a:	b5f0      	push	{r4, r5, r6, r7, lr}
  40037c:	4298      	cmp	r0, r3
  40037e:	d11b      	bne.n	4003b8 <HAL_GPIO_Restore+0x40>
  400380:	2a03      	cmp	r2, #3
  400382:	d11b      	bne.n	4003bc <HAL_GPIO_Restore+0x44>
  400384:	2400      	movs	r4, #0
  400386:	271c      	movs	r7, #28
  400388:	fb07 f604 	mul.w	r6, r7, r4
  40038c:	198d      	adds	r5, r1, r6
  40038e:	598e      	ldr	r6, [r1, r6]
  400390:	eb00 13c4 	add.w	r3, r0, r4, lsl #7
  400394:	605e      	str	r6, [r3, #4]
  400396:	686e      	ldr	r6, [r5, #4]
  400398:	3401      	adds	r4, #1
  40039a:	611e      	str	r6, [r3, #16]
  40039c:	68ee      	ldr	r6, [r5, #12]
  40039e:	42a2      	cmp	r2, r4
  4003a0:	629e      	str	r6, [r3, #40]	@ 0x28
  4003a2:	692e      	ldr	r6, [r5, #16]
  4003a4:	639e      	str	r6, [r3, #56]	@ 0x38
  4003a6:	696e      	ldr	r6, [r5, #20]
  4003a8:	645e      	str	r6, [r3, #68]	@ 0x44
  4003aa:	69ae      	ldr	r6, [r5, #24]
  4003ac:	651e      	str	r6, [r3, #80]	@ 0x50
  4003ae:	68ad      	ldr	r5, [r5, #8]
  4003b0:	61dd      	str	r5, [r3, #28]
  4003b2:	d8e9      	bhi.n	400388 <HAL_GPIO_Restore+0x10>
  4003b4:	2000      	movs	r0, #0
  4003b6:	bdf0      	pop	{r4, r5, r6, r7, pc}
  4003b8:	2a02      	cmp	r2, #2
  4003ba:	e7e2      	b.n	400382 <HAL_GPIO_Restore+0xa>
  4003bc:	2001      	movs	r0, #1
  4003be:	e7fa      	b.n	4003b6 <HAL_GPIO_Restore+0x3e>
  4003c0:	500a0000 	.word	0x500a0000

004003c4 <HAL_RC_locked>:
  4003c4:	b507      	push	{r0, r1, r2, lr}
  4003c6:	2100      	movs	r1, #0
  4003c8:	2002      	movs	r0, #2
  4003ca:	f000 f8ab 	bl	400524 <HAL_MAILBOX_GetMutex>
  4003ce:	2100      	movs	r1, #0
  4003d0:	9001      	str	r0, [sp, #4]
  4003d2:	a801      	add	r0, sp, #4
  4003d4:	f000 f8c2 	bl	40055c <HAL_MAILBOX_Lock>
  4003d8:	3800      	subs	r0, #0
  4003da:	bf18      	it	ne
  4003dc:	2001      	movne	r0, #1
  4003de:	4240      	negs	r0, r0
  4003e0:	b003      	add	sp, #12
  4003e2:	f85d fb04 	ldr.w	pc, [sp], #4

004003e6 <HAL_RC_unlocked>:
  4003e6:	b507      	push	{r0, r1, r2, lr}
  4003e8:	2100      	movs	r1, #0
  4003ea:	2002      	movs	r0, #2
  4003ec:	f000 f89a 	bl	400524 <HAL_MAILBOX_GetMutex>
  4003f0:	2100      	movs	r1, #0
  4003f2:	9001      	str	r0, [sp, #4]
  4003f4:	a801      	add	r0, sp, #4
  4003f6:	f000 f8c3 	bl	400580 <HAL_MAILBOX_UnLock>
  4003fa:	b003      	add	sp, #12
  4003fc:	f85d fb04 	ldr.w	pc, [sp], #4

00400400 <HAL_RC_CAL_GetLPCycle_ex>:
  400400:	4b01      	ldr	r3, [pc, #4]	@ (400408 <HAL_RC_CAL_GetLPCycle_ex+0x8>)
  400402:	7818      	ldrb	r0, [r3, #0]
  400404:	4770      	bx	lr
  400406:	bf00      	nop
  400408:	204015b4 	.word	0x204015b4

0040040c <HAL_RC_CAL_SetLPCycle_ex>:
  40040c:	b118      	cbz	r0, 400416 <HAL_RC_CAL_SetLPCycle_ex+0xa>
  40040e:	4b03      	ldr	r3, [pc, #12]	@ (40041c <HAL_RC_CAL_SetLPCycle_ex+0x10>)
  400410:	7018      	strb	r0, [r3, #0]
  400412:	2000      	movs	r0, #0
  400414:	4770      	bx	lr
  400416:	f04f 30ff 	mov.w	r0, #4294967295
  40041a:	4770      	bx	lr
  40041c:	204015b4 	.word	0x204015b4

00400420 <HAL_RC_CALget_curr_cycle_on_48M>:
  400420:	b573      	push	{r0, r1, r4, r5, r6, lr}
  400422:	4606      	mov	r6, r0
  400424:	460d      	mov	r5, r1
  400426:	f401 fc90 	bl	1d4a <HAL_GetLXTEnabled>
  40042a:	2800      	cmp	r0, #0
  40042c:	d16d      	bne.n	40050a <HAL_RC_CALget_curr_cycle_on_48M+0xea>
  40042e:	f7ff ffc9 	bl	4003c4 <HAL_RC_locked>
  400432:	2800      	cmp	r0, #0
  400434:	d16c      	bne.n	400510 <HAL_RC_CALget_curr_cycle_on_48M+0xf0>
  400436:	4c38      	ldr	r4, [pc, #224]	@ (400518 <HAL_RC_CALget_curr_cycle_on_48M+0xf8>)
  400438:	2001      	movs	r0, #1
  40043a:	f8d4 3114 	ldr.w	r3, [r4, #276]	@ 0x114
  40043e:	f36f 43dc 	bfc	r3, #19, #10
  400442:	f443 2300 	orr.w	r3, r3, #524288	@ 0x80000
  400446:	f8c4 3114 	str.w	r3, [r4, #276]	@ 0x114
  40044a:	f8d4 3114 	ldr.w	r3, [r4, #276]	@ 0x114
  40044e:	f043 5300 	orr.w	r3, r3, #536870912	@ 0x20000000
  400452:	f8c4 3114 	str.w	r3, [r4, #276]	@ 0x114
  400456:	f8d4 3114 	ldr.w	r3, [r4, #276]	@ 0x114
  40045a:	f423 3380 	bic.w	r3, r3, #65536	@ 0x10000
  40045e:	f8c4 3114 	str.w	r3, [r4, #276]	@ 0x114
  400462:	f8d4 3114 	ldr.w	r3, [r4, #276]	@ 0x114
  400466:	f8c4 3114 	str.w	r3, [r4, #276]	@ 0x114
  40046a:	f8d4 3114 	ldr.w	r3, [r4, #276]	@ 0x114
  40046e:	f36f 030f 	bfc	r3, #0, #16
  400472:	f8c4 3114 	str.w	r3, [r4, #276]	@ 0x114
  400476:	f8d4 3114 	ldr.w	r3, [r4, #276]	@ 0x114
  40047a:	431e      	orrs	r6, r3
  40047c:	f8c4 6114 	str.w	r6, [r4, #276]	@ 0x114
  400480:	f8d4 3114 	ldr.w	r3, [r4, #276]	@ 0x114
  400484:	f443 3300 	orr.w	r3, r3, #131072	@ 0x20000
  400488:	f8c4 3114 	str.w	r3, [r4, #276]	@ 0x114
  40048c:	f000 fcec 	bl	400e68 <HAL_Delay>
  400490:	f8d4 3118 	ldr.w	r3, [r4, #280]	@ 0x118
  400494:	2b00      	cmp	r3, #0
  400496:	dafb      	bge.n	400490 <HAL_RC_CALget_curr_cycle_on_48M+0x70>
  400498:	4820      	ldr	r0, [pc, #128]	@ (40051c <HAL_RC_CALget_curr_cycle_on_48M+0xfc>)
  40049a:	f8d4 2118 	ldr.w	r2, [r4, #280]	@ 0x118
  40049e:	6801      	ldr	r1, [r0, #0]
  4004a0:	4e1f      	ldr	r6, [pc, #124]	@ (400520 <HAL_RC_CALget_curr_cycle_on_48M+0x100>)
  4004a2:	f022 4200 	bic.w	r2, r2, #2147483648	@ 0x80000000
  4004a6:	b371      	cbz	r1, 400506 <HAL_RC_CALget_curr_cycle_on_48M+0xe6>
  4004a8:	6833      	ldr	r3, [r6, #0]
  4004aa:	4293      	cmp	r3, r2
  4004ac:	d21d      	bcs.n	4004ea <HAL_RC_CALget_curr_cycle_on_48M+0xca>
  4004ae:	1ad4      	subs	r4, r2, r3
  4004b0:	2cfa      	cmp	r4, #250	@ 0xfa
  4004b2:	d923      	bls.n	4004fc <HAL_RC_CALget_curr_cycle_on_48M+0xdc>
  4004b4:	4299      	cmp	r1, r3
  4004b6:	d921      	bls.n	4004fc <HAL_RC_CALget_curr_cycle_on_48M+0xdc>
  4004b8:	1ac9      	subs	r1, r1, r3
  4004ba:	29fa      	cmp	r1, #250	@ 0xfa
  4004bc:	d91e      	bls.n	4004fc <HAL_RC_CALget_curr_cycle_on_48M+0xdc>
  4004be:	eb03 0443 	add.w	r4, r3, r3, lsl #1
  4004c2:	230d      	movs	r3, #13
  4004c4:	3408      	adds	r4, #8
  4004c6:	fb03 4402 	mla	r4, r3, r2, r4
  4004ca:	0924      	lsrs	r4, r4, #4
  4004cc:	6002      	str	r2, [r0, #0]
  4004ce:	2204      	movs	r2, #4
  4004d0:	2002      	movs	r0, #2
  4004d2:	eb0d 0102 	add.w	r1, sp, r2
  4004d6:	6034      	str	r4, [r6, #0]
  4004d8:	9401      	str	r4, [sp, #4]
  4004da:	f401 fce3 	bl	1ea4 <HAL_LCPU_CONFIG_set>
  4004de:	602c      	str	r4, [r5, #0]
  4004e0:	f7ff ff81 	bl	4003e6 <HAL_RC_unlocked>
  4004e4:	2000      	movs	r0, #0
  4004e6:	b002      	add	sp, #8
  4004e8:	bd70      	pop	{r4, r5, r6, pc}
  4004ea:	d907      	bls.n	4004fc <HAL_RC_CALget_curr_cycle_on_48M+0xdc>
  4004ec:	1a9c      	subs	r4, r3, r2
  4004ee:	2cc8      	cmp	r4, #200	@ 0xc8
  4004f0:	d904      	bls.n	4004fc <HAL_RC_CALget_curr_cycle_on_48M+0xdc>
  4004f2:	4299      	cmp	r1, r3
  4004f4:	d202      	bcs.n	4004fc <HAL_RC_CALget_curr_cycle_on_48M+0xdc>
  4004f6:	1a59      	subs	r1, r3, r1
  4004f8:	29c8      	cmp	r1, #200	@ 0xc8
  4004fa:	e7df      	b.n	4004bc <HAL_RC_CALget_curr_cycle_on_48M+0x9c>
  4004fc:	ebc3 1403 	rsb	r4, r3, r3, lsl #4
  400500:	4414      	add	r4, r2
  400502:	3408      	adds	r4, #8
  400504:	e7e1      	b.n	4004ca <HAL_RC_CALget_curr_cycle_on_48M+0xaa>
  400506:	4614      	mov	r4, r2
  400508:	e7e0      	b.n	4004cc <HAL_RC_CALget_curr_cycle_on_48M+0xac>
  40050a:	f04f 30ff 	mov.w	r0, #4294967295
  40050e:	e7ea      	b.n	4004e6 <HAL_RC_CALget_curr_cycle_on_48M+0xc6>
  400510:	f06f 0002 	mvn.w	r0, #2
  400514:	e7e7      	b.n	4004e6 <HAL_RC_CALget_curr_cycle_on_48M+0xc6>
  400516:	bf00      	nop
  400518:	40090000 	.word	0x40090000
  40051c:	20401a18 	.word	0x20401a18
  400520:	20401a14 	.word	0x20401a14

00400524 <HAL_MAILBOX_GetMutex>:
  400524:	2801      	cmp	r0, #1
  400526:	b508      	push	{r3, lr}
  400528:	d108      	bne.n	40053c <HAL_MAILBOX_GetMutex+0x18>
  40052a:	2903      	cmp	r1, #3
  40052c:	d80e      	bhi.n	40054c <HAL_MAILBOX_GetMutex+0x28>
  40052e:	4808      	ldr	r0, [pc, #32]	@ (400550 <HAL_MAILBOX_GetMutex+0x2c>)
  400530:	e000      	b.n	400534 <HAL_MAILBOX_GetMutex+0x10>
  400532:	4808      	ldr	r0, [pc, #32]	@ (400554 <HAL_MAILBOX_GetMutex+0x30>)
  400534:	2318      	movs	r3, #24
  400536:	fb03 0001 	mla	r0, r3, r1, r0
  40053a:	e008      	b.n	40054e <HAL_MAILBOX_GetMutex+0x2a>
  40053c:	2901      	cmp	r1, #1
  40053e:	d805      	bhi.n	40054c <HAL_MAILBOX_GetMutex+0x28>
  400540:	2802      	cmp	r0, #2
  400542:	d0f6      	beq.n	400532 <HAL_MAILBOX_GetMutex+0xe>
  400544:	21d8      	movs	r1, #216	@ 0xd8
  400546:	4804      	ldr	r0, [pc, #16]	@ (400558 <HAL_MAILBOX_GetMutex+0x34>)
  400548:	f000 fccc 	bl	400ee4 <HAL_AssertFailed>
  40054c:	2000      	movs	r0, #0
  40054e:	bd08      	pop	{r3, pc}
  400550:	50082000 	.word	0x50082000
  400554:	40002000 	.word	0x40002000
  400558:	00401278 	.word	0x00401278

0040055c <HAL_MAILBOX_Lock>:
  40055c:	b508      	push	{r3, lr}
  40055e:	b138      	cbz	r0, 400570 <HAL_MAILBOX_Lock+0x14>
  400560:	6800      	ldr	r0, [r0, #0]
  400562:	b148      	cbz	r0, 400578 <HAL_MAILBOX_Lock+0x1c>
  400564:	6940      	ldr	r0, [r0, #20]
  400566:	2800      	cmp	r0, #0
  400568:	db08      	blt.n	40057c <HAL_MAILBOX_Lock+0x20>
  40056a:	f000 000f 	and.w	r0, r0, #15
  40056e:	bd08      	pop	{r3, pc}
  400570:	2002      	movs	r0, #2
  400572:	f7ff ffd7 	bl	400524 <HAL_MAILBOX_GetMutex>
  400576:	e7f4      	b.n	400562 <HAL_MAILBOX_Lock+0x6>
  400578:	2004      	movs	r0, #4
  40057a:	e7f8      	b.n	40056e <HAL_MAILBOX_Lock+0x12>
  40057c:	2000      	movs	r0, #0
  40057e:	e7f6      	b.n	40056e <HAL_MAILBOX_Lock+0x12>

00400580 <HAL_MAILBOX_UnLock>:
  400580:	b508      	push	{r3, lr}
  400582:	b130      	cbz	r0, 400592 <HAL_MAILBOX_UnLock+0x12>
  400584:	6800      	ldr	r0, [r0, #0]
  400586:	b118      	cbz	r0, 400590 <HAL_MAILBOX_UnLock+0x10>
  400588:	6943      	ldr	r3, [r0, #20]
  40058a:	f043 4300 	orr.w	r3, r3, #2147483648	@ 0x80000000
  40058e:	6143      	str	r3, [r0, #20]
  400590:	bd08      	pop	{r3, pc}
  400592:	2002      	movs	r0, #2
  400594:	f7ff ffc6 	bl	400524 <HAL_MAILBOX_GetMutex>
  400598:	e7f5      	b.n	400586 <HAL_MAILBOX_UnLock+0x6>

0040059a <HAL_MAILBOX_IRQHandler>:
  40059a:	b570      	push	{r4, r5, r6, lr}
  40059c:	4605      	mov	r5, r0
  40059e:	2600      	movs	r6, #0
  4005a0:	6803      	ldr	r3, [r0, #0]
  4005a2:	691c      	ldr	r4, [r3, #16]
  4005a4:	609c      	str	r4, [r3, #8]
  4005a6:	b904      	cbnz	r4, 4005aa <HAL_MAILBOX_IRQHandler+0x10>
  4005a8:	bd70      	pop	{r4, r5, r6, pc}
  4005aa:	07e3      	lsls	r3, r4, #31
  4005ac:	d504      	bpl.n	4005b8 <HAL_MAILBOX_IRQHandler+0x1e>
  4005ae:	68ab      	ldr	r3, [r5, #8]
  4005b0:	b113      	cbz	r3, 4005b8 <HAL_MAILBOX_IRQHandler+0x1e>
  4005b2:	4628      	mov	r0, r5
  4005b4:	b2f1      	uxtb	r1, r6
  4005b6:	4798      	blx	r3
  4005b8:	0864      	lsrs	r4, r4, #1
  4005ba:	3601      	adds	r6, #1
  4005bc:	e7f3      	b.n	4005a6 <HAL_MAILBOX_IRQHandler+0xc>
	...

004005c0 <HAL_PTC_Init>:
  4005c0:	b510      	push	{r4, lr}
  4005c2:	4604      	mov	r4, r0
  4005c4:	b918      	cbnz	r0, 4005ce <HAL_PTC_Init+0xe>
  4005c6:	213d      	movs	r1, #61	@ 0x3d
  4005c8:	480b      	ldr	r0, [pc, #44]	@ (4005f8 <HAL_PTC_Init+0x38>)
  4005ca:	f000 fc8b 	bl	400ee4 <HAL_AssertFailed>
  4005ce:	7d23      	ldrb	r3, [r4, #20]
  4005d0:	2b07      	cmp	r3, #7
  4005d2:	d903      	bls.n	4005dc <HAL_PTC_Init+0x1c>
  4005d4:	213e      	movs	r1, #62	@ 0x3e
  4005d6:	4808      	ldr	r0, [pc, #32]	@ (4005f8 <HAL_PTC_Init+0x38>)
  4005d8:	f000 fc84 	bl	400ee4 <HAL_AssertFailed>
  4005dc:	6823      	ldr	r3, [r4, #0]
  4005de:	7d22      	ldrb	r2, [r4, #20]
  4005e0:	3310      	adds	r3, #16
  4005e2:	eb03 1302 	add.w	r3, r3, r2, lsl #4
  4005e6:	68a2      	ldr	r2, [r4, #8]
  4005e8:	6063      	str	r3, [r4, #4]
  4005ea:	605a      	str	r2, [r3, #4]
  4005ec:	68e2      	ldr	r2, [r4, #12]
  4005ee:	2000      	movs	r0, #0
  4005f0:	609a      	str	r2, [r3, #8]
  4005f2:	2301      	movs	r3, #1
  4005f4:	7623      	strb	r3, [r4, #24]
  4005f6:	bd10      	pop	{r4, pc}
  4005f8:	004012e1 	.word	0x004012e1

004005fc <HAL_PTC_Enable>:
  4005fc:	b530      	push	{r4, r5, lr}
  4005fe:	2401      	movs	r4, #1
  400600:	7d03      	ldrb	r3, [r0, #20]
  400602:	6802      	ldr	r2, [r0, #0]
  400604:	fa04 f303 	lsl.w	r3, r4, r3
  400608:	041d      	lsls	r5, r3, #16
  40060a:	b191      	cbz	r1, 400632 <HAL_PTC_Enable+0x36>
  40060c:	2402      	movs	r4, #2
  40060e:	6851      	ldr	r1, [r2, #4]
  400610:	4319      	orrs	r1, r3
  400612:	f441 3180 	orr.w	r1, r1, #65536	@ 0x10000
  400616:	6051      	str	r1, [r2, #4]
  400618:	6891      	ldr	r1, [r2, #8]
  40061a:	430b      	orrs	r3, r1
  40061c:	432b      	orrs	r3, r5
  40061e:	6093      	str	r3, [r2, #8]
  400620:	7cc2      	ldrb	r2, [r0, #19]
  400622:	7d83      	ldrb	r3, [r0, #22]
  400624:	ea43 4302 	orr.w	r3, r3, r2, lsl #16
  400628:	6842      	ldr	r2, [r0, #4]
  40062a:	6013      	str	r3, [r2, #0]
  40062c:	7604      	strb	r4, [r0, #24]
  40062e:	2000      	movs	r0, #0
  400630:	bd30      	pop	{r4, r5, pc}
  400632:	6891      	ldr	r1, [r2, #8]
  400634:	432b      	orrs	r3, r5
  400636:	ea21 0303 	bic.w	r3, r1, r3
  40063a:	6093      	str	r3, [r2, #8]
  40063c:	e7f6      	b.n	40062c <HAL_PTC_Enable+0x30>

0040063e <HAL_PTC_IRQHandler>:
  40063e:	2301      	movs	r3, #1
  400640:	6802      	ldr	r2, [r0, #0]
  400642:	7d00      	ldrb	r0, [r0, #20]
  400644:	6851      	ldr	r1, [r2, #4]
  400646:	4083      	lsls	r3, r0
  400648:	430b      	orrs	r3, r1
  40064a:	6053      	str	r3, [r2, #4]
  40064c:	4770      	bx	lr
	...

00400650 <RCC_GetModuleMask>:
  400650:	b510      	push	{r4, lr}
  400652:	b15a      	cbz	r2, 40066c <RCC_GetModuleMask+0x1c>
  400654:	b151      	cbz	r1, 40066c <RCC_GetModuleMask+0x1c>
  400656:	2823      	cmp	r0, #35	@ 0x23
  400658:	d05d      	beq.n	400716 <RCC_GetModuleMask+0xc6>
  40065a:	d847      	bhi.n	4006ec <RCC_GetModuleMask+0x9c>
  40065c:	280b      	cmp	r0, #11
  40065e:	d83b      	bhi.n	4006d8 <RCC_GetModuleMask+0x88>
  400660:	b9e0      	cbnz	r0, 40069c <RCC_GetModuleMask+0x4c>
  400662:	f240 314b 	movw	r1, #843	@ 0x34b
  400666:	4841      	ldr	r0, [pc, #260]	@ (40076c <RCC_GetModuleMask+0x11c>)
  400668:	f000 fc3c 	bl	400ee4 <HAL_AssertFailed>
  40066c:	2000      	movs	r0, #0
  40066e:	e051      	b.n	400714 <RCC_GetModuleMask+0xc4>
  400670:	3859      	subs	r0, #89	@ 0x59
  400672:	2807      	cmp	r0, #7
  400674:	d8f5      	bhi.n	400662 <RCC_GetModuleMask+0x12>
  400676:	a401      	add	r4, pc, #4	@ (adr r4, 40067c <RCC_GetModuleMask+0x2c>)
  400678:	f854 f020 	ldr.w	pc, [r4, r0, lsl #2]
  40067c:	00400735 	.word	0x00400735
  400680:	0040074d 	.word	0x0040074d
  400684:	00400755 	.word	0x00400755
  400688:	0040075d 	.word	0x0040075d
  40068c:	00400663 	.word	0x00400663
  400690:	00400663 	.word	0x00400663
  400694:	00400663 	.word	0x00400663
  400698:	00400765 	.word	0x00400765
  40069c:	3801      	subs	r0, #1
  40069e:	2300      	movs	r3, #0
  4006a0:	280a      	cmp	r0, #10
  4006a2:	d8de      	bhi.n	400662 <RCC_GetModuleMask+0x12>
  4006a4:	a401      	add	r4, pc, #4	@ (adr r4, 4006ac <RCC_GetModuleMask+0x5c>)
  4006a6:	f854 f020 	ldr.w	pc, [r4, r0, lsl #2]
  4006aa:	bf00      	nop
  4006ac:	00400747 	.word	0x00400747
  4006b0:	00400663 	.word	0x00400663
  4006b4:	00400663 	.word	0x00400663
  4006b8:	00400741 	.word	0x00400741
  4006bc:	00400663 	.word	0x00400663
  4006c0:	0040073b 	.word	0x0040073b
  4006c4:	00400663 	.word	0x00400663
  4006c8:	00400663 	.word	0x00400663
  4006cc:	00400663 	.word	0x00400663
  4006d0:	0040072f 	.word	0x0040072f
  4006d4:	00400729 	.word	0x00400729
  4006d8:	2816      	cmp	r0, #22
  4006da:	f04f 0300 	mov.w	r3, #0
  4006de:	d01f      	beq.n	400720 <RCC_GetModuleMask+0xd0>
  4006e0:	2822      	cmp	r0, #34	@ 0x22
  4006e2:	d1be      	bne.n	400662 <RCC_GetModuleMask+0x12>
  4006e4:	600b      	str	r3, [r1, #0]
  4006e6:	f44f 7300 	mov.w	r3, #512	@ 0x200
  4006ea:	e010      	b.n	40070e <RCC_GetModuleMask+0xbe>
  4006ec:	2860      	cmp	r0, #96	@ 0x60
  4006ee:	d8b8      	bhi.n	400662 <RCC_GetModuleMask+0x12>
  4006f0:	2858      	cmp	r0, #88	@ 0x58
  4006f2:	f04f 0300 	mov.w	r3, #0
  4006f6:	d8bb      	bhi.n	400670 <RCC_GetModuleMask+0x20>
  4006f8:	2838      	cmp	r0, #56	@ 0x38
  4006fa:	d005      	beq.n	400708 <RCC_GetModuleMask+0xb8>
  4006fc:	283a      	cmp	r0, #58	@ 0x3a
  4006fe:	d1b0      	bne.n	400662 <RCC_GetModuleMask+0x12>
  400700:	600b      	str	r3, [r1, #0]
  400702:	f44f 3380 	mov.w	r3, #65536	@ 0x10000
  400706:	e002      	b.n	40070e <RCC_GetModuleMask+0xbe>
  400708:	600b      	str	r3, [r1, #0]
  40070a:	f44f 7380 	mov.w	r3, #256	@ 0x100
  40070e:	f04f 4080 	mov.w	r0, #1073741824	@ 0x40000000
  400712:	6013      	str	r3, [r2, #0]
  400714:	bd10      	pop	{r4, pc}
  400716:	2300      	movs	r3, #0
  400718:	600b      	str	r3, [r1, #0]
  40071a:	f44f 6380 	mov.w	r3, #1024	@ 0x400
  40071e:	e7f6      	b.n	40070e <RCC_GetModuleMask+0xbe>
  400720:	600b      	str	r3, [r1, #0]
  400722:	f44f 4300 	mov.w	r3, #32768	@ 0x8000
  400726:	e7f2      	b.n	40070e <RCC_GetModuleMask+0xbe>
  400728:	600b      	str	r3, [r1, #0]
  40072a:	2340      	movs	r3, #64	@ 0x40
  40072c:	e7ef      	b.n	40070e <RCC_GetModuleMask+0xbe>
  40072e:	600b      	str	r3, [r1, #0]
  400730:	2320      	movs	r3, #32
  400732:	e7ec      	b.n	40070e <RCC_GetModuleMask+0xbe>
  400734:	600b      	str	r3, [r1, #0]
  400736:	2310      	movs	r3, #16
  400738:	e7e9      	b.n	40070e <RCC_GetModuleMask+0xbe>
  40073a:	600b      	str	r3, [r1, #0]
  40073c:	2308      	movs	r3, #8
  40073e:	e7e6      	b.n	40070e <RCC_GetModuleMask+0xbe>
  400740:	600b      	str	r3, [r1, #0]
  400742:	2304      	movs	r3, #4
  400744:	e7e3      	b.n	40070e <RCC_GetModuleMask+0xbe>
  400746:	600b      	str	r3, [r1, #0]
  400748:	2302      	movs	r3, #2
  40074a:	e7e0      	b.n	40070e <RCC_GetModuleMask+0xbe>
  40074c:	600b      	str	r3, [r1, #0]
  40074e:	f44f 1380 	mov.w	r3, #1048576	@ 0x100000
  400752:	e7dc      	b.n	40070e <RCC_GetModuleMask+0xbe>
  400754:	600b      	str	r3, [r1, #0]
  400756:	f44f 2300 	mov.w	r3, #524288	@ 0x80000
  40075a:	e7d8      	b.n	40070e <RCC_GetModuleMask+0xbe>
  40075c:	600b      	str	r3, [r1, #0]
  40075e:	f44f 2380 	mov.w	r3, #262144	@ 0x40000
  400762:	e7d4      	b.n	40070e <RCC_GetModuleMask+0xbe>
  400764:	600b      	str	r3, [r1, #0]
  400766:	2380      	movs	r3, #128	@ 0x80
  400768:	e7d1      	b.n	40070e <RCC_GetModuleMask+0xbe>
  40076a:	bf00      	nop
  40076c:	00401312 	.word	0x00401312

00400770 <HAL_RCC_EnableModule>:
  400770:	b507      	push	{r0, r1, r2, lr}
  400772:	466a      	mov	r2, sp
  400774:	a901      	add	r1, sp, #4
  400776:	f7ff ff6b 	bl	400650 <RCC_GetModuleMask>
  40077a:	f1b0 4f80 	cmp.w	r0, #1073741824	@ 0x40000000
  40077e:	d101      	bne.n	400784 <HAL_RCC_EnableModule+0x14>
  400780:	9b01      	ldr	r3, [sp, #4]
  400782:	b13b      	cbz	r3, 400794 <HAL_RCC_EnableModule+0x24>
  400784:	f640 013d 	movw	r1, #2109	@ 0x83d
  400788:	4809      	ldr	r0, [pc, #36]	@ (4007b0 <HAL_RCC_EnableModule+0x40>)
  40078a:	b003      	add	sp, #12
  40078c:	f85d eb04 	ldr.w	lr, [sp], #4
  400790:	f000 bba8 	b.w	400ee4 <HAL_AssertFailed>
  400794:	f3ef 8210 	mrs	r2, PRIMASK
  400798:	2301      	movs	r3, #1
  40079a:	f383 8810 	msr	PRIMASK, r3
  40079e:	6843      	ldr	r3, [r0, #4]
  4007a0:	9900      	ldr	r1, [sp, #0]
  4007a2:	430b      	orrs	r3, r1
  4007a4:	6043      	str	r3, [r0, #4]
  4007a6:	f382 8810 	msr	PRIMASK, r2
  4007aa:	b003      	add	sp, #12
  4007ac:	f85d fb04 	ldr.w	pc, [sp], #4
  4007b0:	00401312 	.word	0x00401312

004007b4 <HAL_RCC_MspInit>:
  4007b4:	4770      	bx	lr

004007b6 <HAL_RCC_Init>:
  4007b6:	b508      	push	{r3, lr}
  4007b8:	f7ff fffc 	bl	4007b4 <HAL_RCC_MspInit>
  4007bc:	bd08      	pop	{r3, pc}
	...

004007c0 <bt_audiopath_init>:
  4007c0:	b5f8      	push	{r3, r4, r5, r6, r7, lr}
  4007c2:	4e12      	ldr	r6, [pc, #72]	@ (40080c <bt_audiopath_init+0x4c>)
  4007c4:	4b12      	ldr	r3, [pc, #72]	@ (400810 <bt_audiopath_init+0x50>)
  4007c6:	4c13      	ldr	r4, [pc, #76]	@ (400814 <bt_audiopath_init+0x54>)
  4007c8:	6033      	str	r3, [r6, #0]
  4007ca:	3320      	adds	r3, #32
  4007cc:	6023      	str	r3, [r4, #0]
  4007ce:	4a12      	ldr	r2, [pc, #72]	@ (400818 <bt_audiopath_init+0x58>)
  4007d0:	4b12      	ldr	r3, [pc, #72]	@ (40081c <bt_audiopath_init+0x5c>)
  4007d2:	4f13      	ldr	r7, [pc, #76]	@ (400820 <bt_audiopath_init+0x60>)
  4007d4:	601a      	str	r2, [r3, #0]
  4007d6:	4b13      	ldr	r3, [pc, #76]	@ (400824 <bt_audiopath_init+0x64>)
  4007d8:	4d13      	ldr	r5, [pc, #76]	@ (400828 <bt_audiopath_init+0x68>)
  4007da:	603b      	str	r3, [r7, #0]
  4007dc:	f503 73e6 	add.w	r3, r3, #460	@ 0x1cc
  4007e0:	602b      	str	r3, [r5, #0]
  4007e2:	4b12      	ldr	r3, [pc, #72]	@ (40082c <bt_audiopath_init+0x6c>)
  4007e4:	f502 726b 	add.w	r2, r2, #940	@ 0x3ac
  4007e8:	4811      	ldr	r0, [pc, #68]	@ (400830 <bt_audiopath_init+0x70>)
  4007ea:	601a      	str	r2, [r3, #0]
  4007ec:	f405 f92e 	bl	5a4c <bt_sco_data_handle_callback+0xd0>
  4007f0:	6839      	ldr	r1, [r7, #0]
  4007f2:	6830      	ldr	r0, [r6, #0]
  4007f4:	f44f 72e6 	mov.w	r2, #460	@ 0x1cc
  4007f8:	f454 f9fc 	bl	54bf4 <rt_ringbuffer_getchar+0x63>
  4007fc:	6820      	ldr	r0, [r4, #0]
  4007fe:	f44f 72e6 	mov.w	r2, #460	@ 0x1cc
  400802:	6829      	ldr	r1, [r5, #0]
  400804:	f454 f9f6 	bl	54bf4 <rt_ringbuffer_getchar+0x63>
  400808:	2000      	movs	r0, #0
  40080a:	bdf8      	pop	{r3, r4, r5, r6, r7, pc}
  40080c:	2040e6e8 	.word	0x2040e6e8
  400810:	2040e000 	.word	0x2040e000
  400814:	2040e6ec 	.word	0x2040e6ec
  400818:	2040e040 	.word	0x2040e040
  40081c:	2040e6f0 	.word	0x2040e6f0
  400820:	2040e6f4 	.word	0x2040e6f4
  400824:	2040e050 	.word	0x2040e050
  400828:	2040e6f8 	.word	0x2040e6f8
  40082c:	2040e6fc 	.word	0x2040e6fc
  400830:	0000597d 	.word	0x0000597d

00400834 <patch_install>:
  400834:	4a04      	ldr	r2, [pc, #16]	@ (400848 <patch_install+0x14>)
  400836:	4b05      	ldr	r3, [pc, #20]	@ (40084c <patch_install+0x18>)
  400838:	601a      	str	r2, [r3, #0]
  40083a:	3a01      	subs	r2, #1
  40083c:	6812      	ldr	r2, [r2, #0]
  40083e:	b10a      	cbz	r2, 400844 <patch_install+0x10>
  400840:	681b      	ldr	r3, [r3, #0]
  400842:	4718      	bx	r3
  400844:	4770      	bx	lr
  400846:	bf00      	nop
  400848:	00406001 	.word	0x00406001
  40084c:	20401a1c 	.word	0x20401a1c

00400850 <bluetooth_init>:
  400850:	b510      	push	{r4, lr}
  400852:	2001      	movs	r0, #1
  400854:	f000 f946 	bl	400ae4 <rf_ptc_config>
  400858:	f451 fe4e 	bl	524f8 <rt_hw_ble_int_init>
  40085c:	f401 fa75 	bl	1d4a <HAL_GetLXTEnabled>
  400860:	b928      	cbnz	r0, 40086e <bluetooth_init+0x1e>
  400862:	f450 fcfb 	bl	5125c <rom_config_set_default_sleep_mode+0x7>
  400866:	f7ff fdcb 	bl	400400 <HAL_RC_CAL_GetLPCycle_ex>
  40086a:	f450 fceb 	bl	51244 <rom_config_set_default_link_config+0xb>
  40086e:	2003      	movs	r0, #3
  400870:	f450 fcf8 	bl	51264 <rom_config_set_default_xtal_enabled+0x7>
  400874:	2400      	movs	r4, #0
  400876:	230e      	movs	r3, #14
  400878:	4a0c      	ldr	r2, [pc, #48]	@ (4008ac <bluetooth_init+0x5c>)
  40087a:	490d      	ldr	r1, [pc, #52]	@ (4008b0 <bluetooth_init+0x60>)
  40087c:	4610      	mov	r0, r2
  40087e:	e9c2 4407 	strd	r4, r4, [r2, #28]
  400882:	7513      	strb	r3, [r2, #20]
  400884:	f453 fbc4 	bl	54010 <rt_pm_device_register>
  400888:	480a      	ldr	r0, [pc, #40]	@ (4008b4 <bluetooth_init+0x64>)
  40088a:	f455 fa39 	bl	55d00 <rt_thread_idle_sethook>
  40088e:	480a      	ldr	r0, [pc, #40]	@ (4008b8 <bluetooth_init+0x68>)
  400890:	f453 fc9c 	bl	541cc <rt_pm_override_mode_select>
  400894:	f7ff ffce 	bl	400834 <patch_install>
  400898:	f000 f8c2 	bl	400a20 <bluetooth_config>
  40089c:	f401 fd80 	bl	23a0 <HAL_RCC_SetMacFreq>
  4008a0:	4620      	mov	r0, r4
  4008a2:	f404 fb3b 	bl	4f1c <ble_aon_irq_handler+0x2b>
  4008a6:	4620      	mov	r0, r4
  4008a8:	bd10      	pop	{r4, pc}
  4008aa:	bf00      	nop
  4008ac:	20401a20 	.word	0x20401a20
  4008b0:	004013a8 	.word	0x004013a8
  4008b4:	00017955 	.word	0x00017955
  4008b8:	004008bd 	.word	0x004008bd

004008bc <bluetooth_select_pm_mode>:
  4008bc:	3001      	adds	r0, #1
  4008be:	b508      	push	{r3, lr}
  4008c0:	d001      	beq.n	4008c6 <bluetooth_select_pm_mode+0xa>
  4008c2:	2001      	movs	r0, #1
  4008c4:	bd08      	pop	{r3, pc}
  4008c6:	f417 fa3b 	bl	17d40 <bluetooth_stack_suspend>
  4008ca:	2800      	cmp	r0, #0
  4008cc:	d1f9      	bne.n	4008c2 <bluetooth_select_pm_mode+0x6>
  4008ce:	2003      	movs	r0, #3
  4008d0:	e7f8      	b.n	4008c4 <bluetooth_select_pm_mode+0x8>
	...

004008d4 <bluetooth_pm_suspend>:
  4008d4:	b508      	push	{r3, lr}
  4008d6:	4b09      	ldr	r3, [pc, #36]	@ (4008fc <bluetooth_pm_suspend+0x28>)
  4008d8:	4602      	mov	r2, r0
  4008da:	6a18      	ldr	r0, [r3, #32]
  4008dc:	f010 0020 	ands.w	r0, r0, #32
  4008e0:	d006      	beq.n	4008f0 <bluetooth_pm_suspend+0x1c>
  4008e2:	4b07      	ldr	r3, [pc, #28]	@ (400900 <bluetooth_pm_suspend+0x2c>)
  4008e4:	429a      	cmp	r2, r3
  4008e6:	d104      	bne.n	4008f2 <bluetooth_pm_suspend+0x1e>
  4008e8:	2901      	cmp	r1, #1
  4008ea:	d904      	bls.n	4008f6 <bluetooth_pm_suspend+0x22>
  4008ec:	f417 fa28 	bl	17d40 <bluetooth_stack_suspend>
  4008f0:	bd08      	pop	{r3, pc}
  4008f2:	2000      	movs	r0, #0
  4008f4:	e7fc      	b.n	4008f0 <bluetooth_pm_suspend+0x1c>
  4008f6:	f04f 30ff 	mov.w	r0, #4294967295
  4008fa:	e7f9      	b.n	4008f0 <bluetooth_pm_suspend+0x1c>
  4008fc:	40040000 	.word	0x40040000
  400900:	20401a20 	.word	0x20401a20

00400904 <ble_standby_sleep_pre_handler>:
  400904:	f404 bbac 	b.w	5060 <ble_standby_sleep_after_handler_rom+0x4f>

00400908 <ble_standby_sleep_after_handler>:
  400908:	b508      	push	{r3, lr}
  40090a:	f401 fd49 	bl	23a0 <HAL_RCC_SetMacFreq>
  40090e:	f404 fb7f 	bl	5010 <ble_memory_config+0x18>
  400912:	e8bd 4008 	ldmia.w	sp!, {r3, lr}
  400916:	2000      	movs	r0, #0
  400918:	f000 b8e4 	b.w	400ae4 <rf_ptc_config>

0040091c <rom_port_get>:
  40091c:	b510      	push	{r4, lr}
  40091e:	b148      	cbz	r0, 400934 <rom_port_get+0x18>
  400920:	2801      	cmp	r0, #1
  400922:	d009      	beq.n	400938 <rom_port_get+0x1c>
  400924:	f44f 6207 	mov.w	r2, #2160	@ 0x870
  400928:	4904      	ldr	r1, [pc, #16]	@ (40093c <rom_port_get+0x20>)
  40092a:	4805      	ldr	r0, [pc, #20]	@ (400940 <rom_port_get+0x24>)
  40092c:	f450 fd16 	bl	5135c <rt_assert_handler>
  400930:	4620      	mov	r0, r4
  400932:	bd10      	pop	{r4, pc}
  400934:	2402      	movs	r4, #2
  400936:	e7fb      	b.n	400930 <rom_port_get+0x14>
  400938:	2406      	movs	r4, #6
  40093a:	e7f9      	b.n	400930 <rom_port_get+0x14>
  40093c:	004013c0 	.word	0x004013c0
  400940:	00401354 	.word	0x00401354

00400944 <act_config>:
  400944:	2206      	movs	r2, #6
  400946:	b538      	push	{r3, r4, r5, lr}
  400948:	4c0d      	ldr	r4, [pc, #52]	@ (400980 <act_config+0x3c>)
  40094a:	2302      	movs	r3, #2
  40094c:	2501      	movs	r5, #1
  40094e:	70a2      	strb	r2, [r4, #2]
  400950:	2203      	movs	r2, #3
  400952:	2004      	movs	r0, #4
  400954:	7023      	strb	r3, [r4, #0]
  400956:	70e2      	strb	r2, [r4, #3]
  400958:	7123      	strb	r3, [r4, #4]
  40095a:	7065      	strb	r5, [r4, #1]
  40095c:	f450 fc3c 	bl	511d8 <rom_config_em_memory+0x33>
  400960:	8843      	ldrh	r3, [r0, #2]
  400962:	2014      	movs	r0, #20
  400964:	3b02      	subs	r3, #2
  400966:	71e3      	strb	r3, [r4, #7]
  400968:	f450 fc36 	bl	511d8 <rom_config_em_memory+0x33>
  40096c:	8843      	ldrh	r3, [r0, #2]
  40096e:	7165      	strb	r5, [r4, #5]
  400970:	3b02      	subs	r3, #2
  400972:	7223      	strb	r3, [r4, #8]
  400974:	71a5      	strb	r5, [r4, #6]
  400976:	4620      	mov	r0, r4
  400978:	e8bd 4038 	ldmia.w	sp!, {r3, r4, r5, lr}
  40097c:	f450 bc5c 	b.w	51238 <rom_config_set_controller_enabled+0x7>
  400980:	2040ead4 	.word	0x2040ead4

00400984 <mem_config>:
  400984:	b500      	push	{lr}
  400986:	4a16      	ldr	r2, [pc, #88]	@ (4009e0 <mem_config+0x5c>)
  400988:	b091      	sub	sp, #68	@ 0x44
  40098a:	7953      	ldrb	r3, [r2, #5]
  40098c:	7990      	ldrb	r0, [r2, #6]
  40098e:	005b      	lsls	r3, r3, #1
  400990:	f003 0302 	and.w	r3, r3, #2
  400994:	f000 0001 	and.w	r0, r0, #1
  400998:	4318      	orrs	r0, r3
  40099a:	f450 fc49 	bl	51230 <rom_config_get_default_attribute_4_em+0x57>
  40099e:	2228      	movs	r2, #40	@ 0x28
  4009a0:	2100      	movs	r1, #0
  4009a2:	a806      	add	r0, sp, #24
  4009a4:	f000 fc60 	bl	401268 <memset>
  4009a8:	f44f 7200 	mov.w	r2, #512	@ 0x200
  4009ac:	4b0d      	ldr	r3, [pc, #52]	@ (4009e4 <mem_config+0x60>)
  4009ae:	2106      	movs	r1, #6
  4009b0:	e9cd 3203 	strd	r3, r2, [sp, #12]
  4009b4:	2300      	movs	r3, #0
  4009b6:	e9cd 3101 	strd	r3, r1, [sp, #4]
  4009ba:	f44f 7327 	mov.w	r3, #668	@ 0x29c
  4009be:	2201      	movs	r2, #1
  4009c0:	f44f 5180 	mov.w	r1, #4096	@ 0x1000
  4009c4:	9300      	str	r3, [sp, #0]
  4009c6:	a806      	add	r0, sp, #24
  4009c8:	f44f 5300 	mov.w	r3, #8192	@ 0x2000
  4009cc:	f44f fd80 	bl	504d0 <mem_env_config>
  4009d0:	a806      	add	r0, sp, #24
  4009d2:	f404 fb11 	bl	4ff8 <ble_memory_config>
  4009d6:	f409 fa15 	bl	9e04 <em_config_customized>
  4009da:	b011      	add	sp, #68	@ 0x44
  4009dc:	f85d fb04 	ldr.w	pc, [sp], #4
  4009e0:	2040ead4 	.word	0x2040ead4
  4009e4:	2040fe00 	.word	0x2040fe00

004009e8 <port_config>:
  4009e8:	b510      	push	{r4, lr}
  4009ea:	2000      	movs	r0, #0
  4009ec:	f7ff ff96 	bl	40091c <rom_port_get>
  4009f0:	4b08      	ldr	r3, [pc, #32]	@ (400a14 <port_config+0x2c>)
  4009f2:	f853 3020 	ldr.w	r3, [r3, r0, lsl #2]
  4009f6:	4798      	blx	r3
  4009f8:	4604      	mov	r4, r0
  4009fa:	b928      	cbnz	r0, 400a08 <port_config+0x20>
  4009fc:	f640 12e3 	movw	r2, #2531	@ 0x9e3
  400a00:	4905      	ldr	r1, [pc, #20]	@ (400a18 <port_config+0x30>)
  400a02:	4806      	ldr	r0, [pc, #24]	@ (400a1c <port_config+0x34>)
  400a04:	f450 fcaa 	bl	5135c <rt_assert_handler>
  400a08:	4620      	mov	r0, r4
  400a0a:	e8bd 4010 	ldmia.w	sp!, {r4, lr}
  400a0e:	2100      	movs	r1, #0
  400a10:	f450 bc3a 	b.w	51288 <rom_config_set_swprofiling+0xb>
  400a14:	0005fdcc 	.word	0x0005fdcc
  400a18:	004013b4 	.word	0x004013b4
  400a1c:	00401356 	.word	0x00401356

00400a20 <bluetooth_config>:
  400a20:	b508      	push	{r3, lr}
  400a22:	f7ff ff8f 	bl	400944 <act_config>
  400a26:	f7ff ffad 	bl	400984 <mem_config>
  400a2a:	f7ff ffdd 	bl	4009e8 <port_config>
  400a2e:	bd08      	pop	{r3, pc}

00400a30 <ptc_save_phase>:
  400a30:	4b07      	ldr	r3, [pc, #28]	@ (400a50 <ptc_save_phase+0x20>)
  400a32:	f8d3 2098 	ldr.w	r2, [r3, #152]	@ 0x98
  400a36:	f3c2 030b 	ubfx	r3, r2, #0, #12
  400a3a:	0512      	lsls	r2, r2, #20
  400a3c:	bf44      	itt	mi
  400a3e:	f483 637f 	eormi.w	r3, r3, #4080	@ 0xff0
  400a42:	f083 030f 	eormi.w	r3, r3, #15
  400a46:	b113      	cbz	r3, 400a4e <ptc_save_phase+0x1e>
  400a48:	4a02      	ldr	r2, [pc, #8]	@ (400a54 <ptc_save_phase+0x24>)
  400a4a:	6812      	ldr	r2, [r2, #0]
  400a4c:	6013      	str	r3, [r2, #0]
  400a4e:	4770      	bx	lr
  400a50:	40084000 	.word	0x40084000
  400a54:	204015b8 	.word	0x204015b8

00400a58 <PTC2_IRQHandler>:
  400a58:	4b07      	ldr	r3, [pc, #28]	@ (400a78 <PTC2_IRQHandler+0x20>)
  400a5a:	b510      	push	{r4, lr}
  400a5c:	681c      	ldr	r4, [r3, #0]
  400a5e:	f451 fffb 	bl	52a58 <rt_interrupt_enter>
  400a62:	07a3      	lsls	r3, r4, #30
  400a64:	d504      	bpl.n	400a70 <PTC2_IRQHandler+0x18>
  400a66:	4805      	ldr	r0, [pc, #20]	@ (400a7c <PTC2_IRQHandler+0x24>)
  400a68:	f7ff fde9 	bl	40063e <HAL_PTC_IRQHandler>
  400a6c:	f7ff ffe0 	bl	400a30 <ptc_save_phase>
  400a70:	e8bd 4010 	ldmia.w	sp!, {r4, lr}
  400a74:	f452 b808 	b.w	52a88 <rt_interrupt_leave>
  400a78:	4000c000 	.word	0x4000c000
  400a7c:	20401a60 	.word	0x20401a60

00400a80 <ptc_config>:
  400a80:	b570      	push	{r4, r5, r6, lr}
  400a82:	4616      	mov	r6, r2
  400a84:	221c      	movs	r2, #28
  400a86:	4350      	muls	r0, r2
  400a88:	4d11      	ldr	r5, [pc, #68]	@ (400ad0 <ptc_config+0x50>)
  400a8a:	4a12      	ldr	r2, [pc, #72]	@ (400ad4 <ptc_config+0x54>)
  400a8c:	182c      	adds	r4, r5, r0
  400a8e:	502a      	str	r2, [r5, r0]
  400a90:	2201      	movs	r2, #1
  400a92:	7522      	strb	r2, [r4, #20]
  400a94:	4a10      	ldr	r2, [pc, #64]	@ (400ad8 <ptc_config+0x58>)
  400a96:	2005      	movs	r0, #5
  400a98:	6812      	ldr	r2, [r2, #0]
  400a9a:	74e0      	strb	r0, [r4, #19]
  400a9c:	60a2      	str	r2, [r4, #8]
  400a9e:	2200      	movs	r2, #0
  400aa0:	2012      	movs	r0, #18
  400aa2:	75a1      	strb	r1, [r4, #22]
  400aa4:	4611      	mov	r1, r2
  400aa6:	60e2      	str	r2, [r4, #12]
  400aa8:	74a6      	strb	r6, [r4, #18]
  400aaa:	8223      	strh	r3, [r4, #16]
  400aac:	f401 fafe 	bl	20ac <HAL_NVIC_SetPriority>
  400ab0:	4620      	mov	r0, r4
  400ab2:	f7ff fd85 	bl	4005c0 <HAL_PTC_Init>
  400ab6:	b128      	cbz	r0, 400ac4 <ptc_config+0x44>
  400ab8:	f240 125f 	movw	r2, #351	@ 0x15f
  400abc:	4907      	ldr	r1, [pc, #28]	@ (400adc <ptc_config+0x5c>)
  400abe:	4808      	ldr	r0, [pc, #32]	@ (400ae0 <ptc_config+0x60>)
  400ac0:	f450 fc4c 	bl	5135c <rt_assert_handler>
  400ac4:	4620      	mov	r0, r4
  400ac6:	e8bd 4070 	ldmia.w	sp!, {r4, r5, r6, lr}
  400aca:	2101      	movs	r1, #1
  400acc:	f7ff bd96 	b.w	4005fc <HAL_PTC_Enable>
  400ad0:	20401a60 	.word	0x20401a60
  400ad4:	4000c000 	.word	0x4000c000
  400ad8:	204015b8 	.word	0x204015b8
  400adc:	004013cd 	.word	0x004013cd
  400ae0:	00401359 	.word	0x00401359

00400ae4 <rf_ptc_config>:
  400ae4:	b510      	push	{r4, lr}
  400ae6:	b128      	cbz	r0, 400af4 <rf_ptc_config+0x10>
  400ae8:	2200      	movs	r2, #0
  400aea:	4b08      	ldr	r3, [pc, #32]	@ (400b0c <rf_ptc_config+0x28>)
  400aec:	681b      	ldr	r3, [r3, #0]
  400aee:	601a      	str	r2, [r3, #0]
  400af0:	605a      	str	r2, [r3, #4]
  400af2:	811a      	strh	r2, [r3, #8]
  400af4:	2038      	movs	r0, #56	@ 0x38
  400af6:	f7ff fe3b 	bl	400770 <HAL_RCC_EnableModule>
  400afa:	e8bd 4010 	ldmia.w	sp!, {r4, lr}
  400afe:	2300      	movs	r3, #0
  400b00:	2169      	movs	r1, #105	@ 0x69
  400b02:	461a      	mov	r2, r3
  400b04:	4618      	mov	r0, r3
  400b06:	f7ff bfbb 	b.w	400a80 <ptc_config>
  400b0a:	bf00      	nop
  400b0c:	204015b8 	.word	0x204015b8

00400b10 <hcpu2lcpu_notification_callback>:
  400b10:	2907      	cmp	r1, #7
  400b12:	b510      	push	{r4, lr}
  400b14:	460c      	mov	r4, r1
  400b16:	d904      	bls.n	400b22 <hcpu2lcpu_notification_callback+0x12>
  400b18:	225d      	movs	r2, #93	@ 0x5d
  400b1a:	490a      	ldr	r1, [pc, #40]	@ (400b44 <hcpu2lcpu_notification_callback+0x34>)
  400b1c:	480a      	ldr	r0, [pc, #40]	@ (400b48 <hcpu2lcpu_notification_callback+0x38>)
  400b1e:	f450 fc1d 	bl	5135c <rt_assert_handler>
  400b22:	4b0a      	ldr	r3, [pc, #40]	@ (400b4c <hcpu2lcpu_notification_callback+0x3c>)
  400b24:	6a5a      	ldr	r2, [r3, #36]	@ 0x24
  400b26:	40e2      	lsrs	r2, r4
  400b28:	07d2      	lsls	r2, r2, #31
  400b2a:	d503      	bpl.n	400b34 <hcpu2lcpu_notification_callback+0x24>
  400b2c:	b91c      	cbnz	r4, 400b36 <hcpu2lcpu_notification_callback+0x26>
  400b2e:	6a98      	ldr	r0, [r3, #40]	@ 0x28
  400b30:	f415 fe06 	bl	16740 <ipc_queue_data_ind_rom>
  400b34:	bd10      	pop	{r4, pc}
  400b36:	eb03 0384 	add.w	r3, r3, r4, lsl #2
  400b3a:	6a98      	ldr	r0, [r3, #40]	@ 0x28
  400b3c:	e8bd 4010 	ldmia.w	sp!, {r4, lr}
  400b40:	f415 bde2 	b.w	16708 <ipc_queue_data_ind>
  400b44:	004013d8 	.word	0x004013d8
  400b48:	00401362 	.word	0x00401362
  400b4c:	2040e498 	.word	0x2040e498

00400b50 <HCPU2LCPU_IRQHandler>:
  400b50:	b508      	push	{r3, lr}
  400b52:	f451 ff81 	bl	52a58 <rt_interrupt_enter>
  400b56:	4803      	ldr	r0, [pc, #12]	@ (400b64 <HCPU2LCPU_IRQHandler+0x14>)
  400b58:	f7ff fd1f 	bl	40059a <HAL_MAILBOX_IRQHandler>
  400b5c:	e8bd 4008 	ldmia.w	sp!, {r3, lr}
  400b60:	f451 bf92 	b.w	52a88 <rt_interrupt_leave>
  400b64:	204015bc 	.word	0x204015bc

00400b68 <sys_init_debug_trigger>:
  400b68:	4a06      	ldr	r2, [pc, #24]	@ (400b84 <sys_init_debug_trigger+0x1c>)
  400b6a:	b508      	push	{r3, lr}
  400b6c:	6913      	ldr	r3, [r2, #16]
  400b6e:	4806      	ldr	r0, [pc, #24]	@ (400b88 <sys_init_debug_trigger+0x20>)
  400b70:	f043 5300 	orr.w	r3, r3, #536870912	@ 0x20000000
  400b74:	6113      	str	r3, [r2, #16]
  400b76:	f450 fc0f 	bl	51398 <rt_assert_set_hook>
  400b7a:	4804      	ldr	r0, [pc, #16]	@ (400b8c <sys_init_debug_trigger+0x24>)
  400b7c:	f451 fd48 	bl	52610 <rt_hw_exception_install>
  400b80:	2000      	movs	r0, #0
  400b82:	bd08      	pop	{r3, pc}
  400b84:	4000f000 	.word	0x4000f000
  400b88:	00400bb1 	.word	0x00400bb1
  400b8c:	00400b91 	.word	0x00400b91

00400b90 <exception_handler>:
  400b90:	b510      	push	{r4, lr}
  400b92:	4c06      	ldr	r4, [pc, #24]	@ (400bac <exception_handler+0x1c>)
  400b94:	6923      	ldr	r3, [r4, #16]
  400b96:	005b      	lsls	r3, r3, #1
  400b98:	d406      	bmi.n	400ba8 <exception_handler+0x18>
  400b9a:	2001      	movs	r0, #1
  400b9c:	f401 fa2a 	bl	1ff4 <HAL_LPAON_WakeCore>
  400ba0:	6923      	ldr	r3, [r4, #16]
  400ba2:	f043 5380 	orr.w	r3, r3, #268435456	@ 0x10000000
  400ba6:	6123      	str	r3, [r4, #16]
  400ba8:	2001      	movs	r0, #1
  400baa:	bd10      	pop	{r4, pc}
  400bac:	4000f000 	.word	0x4000f000

00400bb0 <assert_hook>:
  400bb0:	b510      	push	{r4, lr}
  400bb2:	4c08      	ldr	r4, [pc, #32]	@ (400bd4 <assert_hook+0x24>)
  400bb4:	6923      	ldr	r3, [r4, #16]
  400bb6:	005b      	lsls	r3, r3, #1
  400bb8:	d40a      	bmi.n	400bd0 <assert_hook+0x20>
  400bba:	2001      	movs	r0, #1
  400bbc:	f401 fa1a 	bl	1ff4 <HAL_LPAON_WakeCore>
  400bc0:	6923      	ldr	r3, [r4, #16]
  400bc2:	f043 5380 	orr.w	r3, r3, #268435456	@ 0x10000000
  400bc6:	6123      	str	r3, [r4, #16]
  400bc8:	e8bd 4010 	ldmia.w	sp!, {r4, lr}
  400bcc:	f000 bb1e 	b.w	40120c <rt_hw_fatal_error>
  400bd0:	bd10      	pop	{r4, pc}
  400bd2:	bf00      	nop
  400bd4:	4000f000 	.word	0x4000f000

00400bd8 <DBG_Trigger_IRQHandler>:
  400bd8:	b508      	push	{r3, lr}
  400bda:	f451 ff3d 	bl	52a58 <rt_interrupt_enter>
  400bde:	f240 1269 	movw	r2, #361	@ 0x169
  400be2:	4904      	ldr	r1, [pc, #16]	@ (400bf4 <DBG_Trigger_IRQHandler+0x1c>)
  400be4:	4804      	ldr	r0, [pc, #16]	@ (400bf8 <DBG_Trigger_IRQHandler+0x20>)
  400be6:	f450 fbb9 	bl	5135c <rt_assert_handler>
  400bea:	e8bd 4008 	ldmia.w	sp!, {r3, lr}
  400bee:	f451 bf4b 	b.w	52a88 <rt_interrupt_leave>
  400bf2:	bf00      	nop
  400bf4:	004013f8 	.word	0x004013f8
  400bf8:	00401354 	.word	0x00401354

00400bfc <sifli_exit_idle>:
  400bfc:	4770      	bx	lr

00400bfe <sifli_resume>:
  400bfe:	4770      	bx	lr

00400c00 <sifli_suspend>:
  400c00:	2901      	cmp	r1, #1
  400c02:	b508      	push	{r3, lr}
  400c04:	d801      	bhi.n	400c0a <sifli_suspend+0xa>
  400c06:	2000      	movs	r0, #0
  400c08:	bd08      	pop	{r3, pc}
  400c0a:	f415 fd37 	bl	1667c <ipc_queue_check_idle>
  400c0e:	b908      	cbnz	r0, 400c14 <sifli_suspend+0x14>
  400c10:	2007      	movs	r0, #7
  400c12:	e7f9      	b.n	400c08 <sifli_suspend+0x8>
  400c14:	f415 fd50 	bl	166b8 <ipc_queue_check_idle_rom>
  400c18:	2800      	cmp	r0, #0
  400c1a:	d0f9      	beq.n	400c10 <sifli_suspend+0x10>
  400c1c:	4b02      	ldr	r3, [pc, #8]	@ (400c28 <sifli_suspend+0x28>)
  400c1e:	6a5a      	ldr	r2, [r3, #36]	@ 0x24
  400c20:	6a1b      	ldr	r3, [r3, #32]
  400c22:	421a      	tst	r2, r3
  400c24:	d0ef      	beq.n	400c06 <sifli_suspend+0x6>
  400c26:	e7f3      	b.n	400c10 <sifli_suspend+0x10>
  400c28:	40040000 	.word	0x40040000

00400c2c <rt_application_init_power_on_mode>:
  400c2c:	4770      	bx	lr

00400c2e <SystemPowerOnModeInit>:
  400c2e:	b508      	push	{r3, lr}
  400c30:	f000 fc58 	bl	4014e4 <SystemPowerOnInitLCPU>
  400c34:	bd08      	pop	{r3, pc}
	...

00400c38 <SystemPowerOnModeGet>:
  400c38:	4b01      	ldr	r3, [pc, #4]	@ (400c40 <SystemPowerOnModeGet+0x8>)
  400c3a:	7818      	ldrb	r0, [r3, #0]
  400c3c:	4770      	bx	lr
  400c3e:	bf00      	nop
  400c40:	2040fd54 	.word	0x2040fd54

00400c44 <sifli_standby_handler>:
  400c44:	b510      	push	{r4, lr}
  400c46:	4c0f      	ldr	r4, [pc, #60]	@ (400c84 <sifli_standby_handler+0x40>)
  400c48:	6a23      	ldr	r3, [r4, #32]
  400c4a:	069a      	lsls	r2, r3, #26
  400c4c:	d406      	bmi.n	400c5c <sifli_standby_handler+0x18>
  400c4e:	f459 fdd5 	bl	5a7fc <sifli_standby_handler_core>
  400c52:	6a23      	ldr	r3, [r4, #32]
  400c54:	069b      	lsls	r3, r3, #26
  400c56:	d40b      	bmi.n	400c70 <sifli_standby_handler+0x2c>
  400c58:	2000      	movs	r0, #0
  400c5a:	bd10      	pop	{r4, pc}
  400c5c:	4b0a      	ldr	r3, [pc, #40]	@ (400c88 <sifli_standby_handler+0x44>)
  400c5e:	2b00      	cmp	r3, #0
  400c60:	d0f5      	beq.n	400c4e <sifli_standby_handler+0xa>
  400c62:	f7ff fe4f 	bl	400904 <ble_standby_sleep_pre_handler>
  400c66:	2800      	cmp	r0, #0
  400c68:	d0f1      	beq.n	400c4e <sifli_standby_handler+0xa>
  400c6a:	f04f 30ff 	mov.w	r0, #4294967295
  400c6e:	e7f4      	b.n	400c5a <sifli_standby_handler+0x16>
  400c70:	4c06      	ldr	r4, [pc, #24]	@ (400c8c <sifli_standby_handler+0x48>)
  400c72:	6823      	ldr	r3, [r4, #0]
  400c74:	2b00      	cmp	r3, #0
  400c76:	d0ef      	beq.n	400c58 <sifli_standby_handler+0x14>
  400c78:	f7ff fe46 	bl	400908 <ble_standby_sleep_after_handler>
  400c7c:	2300      	movs	r3, #0
  400c7e:	6023      	str	r3, [r4, #0]
  400c80:	e7ea      	b.n	400c58 <sifli_standby_handler+0x14>
  400c82:	bf00      	nop
  400c84:	40040000 	.word	0x40040000
  400c88:	00400905 	.word	0x00400905
  400c8c:	20401aec 	.word	0x20401aec

00400c90 <low_power_init>:
  400c90:	b510      	push	{r4, lr}
  400c92:	2200      	movs	r2, #0
  400c94:	21fc      	movs	r1, #252	@ 0xfc
  400c96:	480c      	ldr	r0, [pc, #48]	@ (400cc8 <low_power_init+0x38>)
  400c98:	f454 fcb4 	bl	55604 <rt_system_pm_init>
  400c9c:	2001      	movs	r0, #1
  400c9e:	490b      	ldr	r1, [pc, #44]	@ (400ccc <low_power_init+0x3c>)
  400ca0:	f453 fa98 	bl	541d4 <rt_pm_policy_register>
  400ca4:	490a      	ldr	r1, [pc, #40]	@ (400cd0 <low_power_init+0x40>)
  400ca6:	2000      	movs	r0, #0
  400ca8:	f453 f9b2 	bl	54010 <rt_pm_device_register>
  400cac:	f415 fbe2 	bl	16474 <init_default_wakeup_src>
  400cb0:	4b08      	ldr	r3, [pc, #32]	@ (400cd4 <low_power_init+0x44>)
  400cb2:	4c09      	ldr	r4, [pc, #36]	@ (400cd8 <low_power_init+0x48>)
  400cb4:	6c9b      	ldr	r3, [r3, #72]	@ 0x48
  400cb6:	60a3      	str	r3, [r4, #8]
  400cb8:	f455 fa92 	bl	561e0 <rt_tick_get>
  400cbc:	2301      	movs	r3, #1
  400cbe:	60e0      	str	r0, [r4, #12]
  400cc0:	7023      	strb	r3, [r4, #0]
  400cc2:	2000      	movs	r0, #0
  400cc4:	bd10      	pop	{r4, pc}
  400cc6:	bf00      	nop
  400cc8:	204015c8 	.word	0x204015c8
  400ccc:	0040142c 	.word	0x0040142c
  400cd0:	00401420 	.word	0x00401420
  400cd4:	40040000 	.word	0x40040000
  400cd8:	20401acc 	.word	0x20401acc

00400cdc <sifli_shutdown_handler>:
  400cdc:	4770      	bx	lr
	...

00400ce0 <sifli_sleep>:
  400ce0:	b5f8      	push	{r3, r4, r5, r6, r7, lr}
  400ce2:	4b2c      	ldr	r3, [pc, #176]	@ (400d94 <sifli_sleep+0xb4>)
  400ce4:	6019      	str	r1, [r3, #0]
  400ce6:	3902      	subs	r1, #2
  400ce8:	2903      	cmp	r1, #3
  400cea:	d805      	bhi.n	400cf8 <sifli_sleep+0x18>
  400cec:	e8df f001 	tbb	[pc, r1]
  400cf0:	0209414a 	.word	0x0209414a
  400cf4:	f7ff fff2 	bl	400cdc <sifli_shutdown_handler>
  400cf8:	4b27      	ldr	r3, [pc, #156]	@ (400d98 <sifli_sleep+0xb8>)
  400cfa:	6a5a      	ldr	r2, [r3, #36]	@ 0x24
  400cfc:	4b27      	ldr	r3, [pc, #156]	@ (400d9c <sifli_sleep+0xbc>)
  400cfe:	601a      	str	r2, [r3, #0]
  400d00:	e03f      	b.n	400d82 <sifli_sleep+0xa2>
  400d02:	2009      	movs	r0, #9
  400d04:	f452 ffc8 	bl	53c98 <rt_object_get_information>
  400d08:	4604      	mov	r4, r0
  400d0a:	6845      	ldr	r5, [r0, #4]
  400d0c:	1d07      	adds	r7, r0, #4
  400d0e:	42bd      	cmp	r5, r7
  400d10:	d11d      	bne.n	400d4e <sifli_sleep+0x6e>
  400d12:	4e21      	ldr	r6, [pc, #132]	@ (400d98 <sifli_sleep+0xb8>)
  400d14:	f7ff ff96 	bl	400c44 <sifli_standby_handler>
  400d18:	6cb2      	ldr	r2, [r6, #72]	@ 0x48
  400d1a:	4b21      	ldr	r3, [pc, #132]	@ (400da0 <sifli_sleep+0xc0>)
  400d1c:	4821      	ldr	r0, [pc, #132]	@ (400da4 <sifli_sleep+0xc4>)
  400d1e:	619a      	str	r2, [r3, #24]
  400d20:	f450 ffb8 	bl	51c94 <rt_device_find>
  400d24:	4605      	mov	r5, r0
  400d26:	b118      	cbz	r0, 400d30 <sifli_sleep+0x50>
  400d28:	2204      	movs	r2, #4
  400d2a:	2101      	movs	r1, #1
  400d2c:	f450 ff38 	bl	51ba0 <rt_device_control>
  400d30:	6c73      	ldr	r3, [r6, #68]	@ 0x44
  400d32:	481d      	ldr	r0, [pc, #116]	@ (400da8 <sifli_sleep+0xc8>)
  400d34:	f023 0301 	bic.w	r3, r3, #1
  400d38:	6473      	str	r3, [r6, #68]	@ 0x44
  400d3a:	f400 ffef 	bl	1d1c <HAL_GPIO_ClearInterrupt>
  400d3e:	6864      	ldr	r4, [r4, #4]
  400d40:	42bc      	cmp	r4, r7
  400d42:	d10c      	bne.n	400d5e <sifli_sleep+0x7e>
  400d44:	f415 fe3a 	bl	169bc <ipc_queue_restore_all>
  400d48:	f415 fe6c 	bl	16a24 <ipc_queue_restore_all_rom>
  400d4c:	e7d4      	b.n	400cf8 <sifli_sleep+0x18>
  400d4e:	f1a5 000c 	sub.w	r0, r5, #12
  400d52:	2204      	movs	r2, #4
  400d54:	2102      	movs	r1, #2
  400d56:	f450 ff23 	bl	51ba0 <rt_device_control>
  400d5a:	682d      	ldr	r5, [r5, #0]
  400d5c:	e7d7      	b.n	400d0e <sifli_sleep+0x2e>
  400d5e:	f1a4 000c 	sub.w	r0, r4, #12
  400d62:	4285      	cmp	r5, r0
  400d64:	d003      	beq.n	400d6e <sifli_sleep+0x8e>
  400d66:	2204      	movs	r2, #4
  400d68:	2101      	movs	r1, #1
  400d6a:	f450 ff19 	bl	51ba0 <rt_device_control>
  400d6e:	6824      	ldr	r4, [r4, #0]
  400d70:	e7e6      	b.n	400d40 <sifli_sleep+0x60>
  400d72:	f459 fbe1 	bl	5a538 <sifli_deep_handler>
  400d76:	4b08      	ldr	r3, [pc, #32]	@ (400d98 <sifli_sleep+0xb8>)
  400d78:	2800      	cmp	r0, #0
  400d7a:	6c9a      	ldr	r2, [r3, #72]	@ 0x48
  400d7c:	4b08      	ldr	r3, [pc, #32]	@ (400da0 <sifli_sleep+0xc0>)
  400d7e:	619a      	str	r2, [r3, #24]
  400d80:	dbba      	blt.n	400cf8 <sifli_sleep+0x18>
  400d82:	bdf8      	pop	{r3, r4, r5, r6, r7, pc}
  400d84:	f459 fc24 	bl	5a5d0 <sifli_light_handler>
  400d88:	4b03      	ldr	r3, [pc, #12]	@ (400d98 <sifli_sleep+0xb8>)
  400d8a:	6c9a      	ldr	r2, [r3, #72]	@ 0x48
  400d8c:	4b04      	ldr	r3, [pc, #16]	@ (400da0 <sifli_sleep+0xc0>)
  400d8e:	619a      	str	r2, [r3, #24]
  400d90:	e7b2      	b.n	400cf8 <sifli_sleep+0x18>
  400d92:	bf00      	nop
  400d94:	2040e8c0 	.word	0x2040e8c0
  400d98:	40040000 	.word	0x40040000
  400d9c:	2040fd58 	.word	0x2040fd58
  400da0:	20401acc 	.word	0x20401acc
  400da4:	00401389 	.word	0x00401389
  400da8:	40080000 	.word	0x40080000

00400dac <pm_set_last_latch_tick>:
  400dac:	4b01      	ldr	r3, [pc, #4]	@ (400db4 <pm_set_last_latch_tick+0x8>)
  400dae:	60d8      	str	r0, [r3, #12]
  400db0:	4770      	bx	lr
  400db2:	bf00      	nop
  400db4:	20401acc 	.word	0x20401acc

00400db8 <AON_IRQHandler>:
  400db8:	b508      	push	{r3, lr}
  400dba:	f451 fe4d 	bl	52a58 <rt_interrupt_enter>
  400dbe:	f400 fb11 	bl	13e4 <AON_LCPU_IRQHandler>
  400dc2:	e8bd 4008 	ldmia.w	sp!, {r3, lr}
  400dc6:	f451 be5f 	b.w	52a88 <rt_interrupt_leave>

00400dca <wdt_store_exception_information>:
  400dca:	4770      	bx	lr

00400dcc <WDT_IRQHandler>:
  400dcc:	b538      	push	{r3, r4, r5, lr}
  400dce:	4b18      	ldr	r3, [pc, #96]	@ (400e30 <WDT_IRQHandler+0x64>)
  400dd0:	681a      	ldr	r2, [r3, #0]
  400dd2:	bb2a      	cbnz	r2, 400e20 <WDT_IRQHandler+0x54>
  400dd4:	2401      	movs	r4, #1
  400dd6:	4d17      	ldr	r5, [pc, #92]	@ (400e34 <WDT_IRQHandler+0x68>)
  400dd8:	601c      	str	r4, [r3, #0]
  400dda:	692b      	ldr	r3, [r5, #16]
  400ddc:	005a      	lsls	r2, r3, #1
  400dde:	d41f      	bmi.n	400e20 <WDT_IRQHandler+0x54>
  400de0:	f7ff fff3 	bl	400dca <wdt_store_exception_information>
  400de4:	4620      	mov	r0, r4
  400de6:	f401 f905 	bl	1ff4 <HAL_LPAON_WakeCore>
  400dea:	692b      	ldr	r3, [r5, #16]
  400dec:	4620      	mov	r0, r4
  400dee:	f043 5380 	orr.w	r3, r3, #268435456	@ 0x10000000
  400df2:	612b      	str	r3, [r5, #16]
  400df4:	4b10      	ldr	r3, [pc, #64]	@ (400e38 <WDT_IRQHandler+0x6c>)
  400df6:	4d11      	ldr	r5, [pc, #68]	@ (400e3c <WDT_IRQHandler+0x70>)
  400df8:	f64b 3481 	movw	r4, #48001	@ 0xbb81
  400dfc:	602b      	str	r3, [r5, #0]
  400dfe:	f000 f833 	bl	400e68 <HAL_Delay>
  400e02:	2234      	movs	r2, #52	@ 0x34
  400e04:	682b      	ldr	r3, [r5, #0]
  400e06:	60da      	str	r2, [r3, #12]
  400e08:	682b      	ldr	r3, [r5, #0]
  400e0a:	695b      	ldr	r3, [r3, #20]
  400e0c:	079b      	lsls	r3, r3, #30
  400e0e:	d408      	bmi.n	400e22 <WDT_IRQHandler+0x56>
  400e10:	2001      	movs	r0, #1
  400e12:	f000 f829 	bl	400e68 <HAL_Delay>
  400e16:	4a07      	ldr	r2, [pc, #28]	@ (400e34 <WDT_IRQHandler+0x68>)
  400e18:	6813      	ldr	r3, [r2, #0]
  400e1a:	f043 0301 	orr.w	r3, r3, #1
  400e1e:	6013      	str	r3, [r2, #0]
  400e20:	bd38      	pop	{r3, r4, r5, pc}
  400e22:	3c01      	subs	r4, #1
  400e24:	d0f4      	beq.n	400e10 <WDT_IRQHandler+0x44>
  400e26:	2001      	movs	r0, #1
  400e28:	f400 ff50 	bl	1ccc <HAL_Delay_us_>
  400e2c:	e7ec      	b.n	400e08 <WDT_IRQHandler+0x3c>
  400e2e:	bf00      	nop
  400e30:	20401af0 	.word	0x20401af0
  400e34:	4000f000 	.word	0x4000f000
  400e38:	4000b000 	.word	0x4000b000
  400e3c:	20401af4 	.word	0x20401af4

00400e40 <lcpu_thread_init_hook>:
  400e40:	6ac2      	ldr	r2, [r0, #44]	@ 0x2c
  400e42:	6a81      	ldr	r1, [r0, #40]	@ 0x28
  400e44:	3a04      	subs	r2, #4
  400e46:	b510      	push	{r4, lr}
  400e48:	440a      	add	r2, r1
  400e4a:	4604      	mov	r4, r0
  400e4c:	e9d0 0108 	ldrd	r0, r1, [r0, #32]
  400e50:	4b04      	ldr	r3, [pc, #16]	@ (400e64 <lcpu_thread_init_hook+0x24>)
  400e52:	f451 fc03 	bl	5265c <rt_hw_stack_init>
  400e56:	6aa1      	ldr	r1, [r4, #40]	@ 0x28
  400e58:	61e0      	str	r0, [r4, #28]
  400e5a:	e8bd 4010 	ldmia.w	sp!, {r4, lr}
  400e5e:	f000 b92d 	b.w	4010bc <rt_hw_set_stack_limit>
  400e62:	bf00      	nop
  400e64:	00055ad1 	.word	0x00055ad1

00400e68 <HAL_Delay>:
  400e68:	b507      	push	{r0, r1, r2, lr}
  400e6a:	9001      	str	r0, [sp, #4]
  400e6c:	9b01      	ldr	r3, [sp, #4]
  400e6e:	b913      	cbnz	r3, 400e76 <HAL_Delay+0xe>
  400e70:	b003      	add	sp, #12
  400e72:	f85d fb04 	ldr.w	pc, [sp], #4
  400e76:	f44f 707a 	mov.w	r0, #1000	@ 0x3e8
  400e7a:	f7ff fa4d 	bl	400318 <HAL_Delay_us>
  400e7e:	9b01      	ldr	r3, [sp, #4]
  400e80:	3b01      	subs	r3, #1
  400e82:	9301      	str	r3, [sp, #4]
  400e84:	e7f2      	b.n	400e6c <HAL_Delay+0x4>

00400e86 <HAL_InitTick>:
  400e86:	2000      	movs	r0, #0
  400e88:	4770      	bx	lr
	...

00400e8c <SysTick_Handler>:
  400e8c:	b570      	push	{r4, r5, r6, lr}
  400e8e:	4d14      	ldr	r5, [pc, #80]	@ (400ee0 <SysTick_Handler+0x54>)
  400e90:	f451 fde2 	bl	52a58 <rt_interrupt_enter>
  400e94:	6a6b      	ldr	r3, [r5, #36]	@ 0x24
  400e96:	f7ff fa37 	bl	400308 <HAL_IncTick>
  400e9a:	f455 f9a1 	bl	561e0 <rt_tick_get>
  400e9e:	6aeb      	ldr	r3, [r5, #44]	@ 0x2c
  400ea0:	4604      	mov	r4, r0
  400ea2:	069b      	lsls	r3, r3, #26
  400ea4:	d405      	bmi.n	400eb2 <SysTick_Handler+0x26>
  400ea6:	f455 f9a3 	bl	561f0 <rt_tick_increase>
  400eaa:	e8bd 4070 	ldmia.w	sp!, {r4, r5, r6, lr}
  400eae:	f451 bdeb 	b.w	52a88 <rt_interrupt_leave>
  400eb2:	6cad      	ldr	r5, [r5, #72]	@ 0x48
  400eb4:	1c46      	adds	r6, r0, #1
  400eb6:	f401 f8ad 	bl	2014 <HAL_LPTIM_GetFreq>
  400eba:	2301      	movs	r3, #1
  400ebc:	4602      	mov	r2, r0
  400ebe:	4629      	mov	r1, r5
  400ec0:	4630      	mov	r0, r6
  400ec2:	f44f fd09 	bl	508d8 <pm_latch_tick>
  400ec6:	4284      	cmp	r4, r0
  400ec8:	d0ef      	beq.n	400eaa <SysTick_Handler+0x1e>
  400eca:	4286      	cmp	r6, r0
  400ecc:	d0eb      	beq.n	400ea6 <SysTick_Handler+0x1a>
  400ece:	f455 f98f 	bl	561f0 <rt_tick_increase>
  400ed2:	f455 f98d 	bl	561f0 <rt_tick_increase>
  400ed6:	1ca0      	adds	r0, r4, #2
  400ed8:	f7ff ff68 	bl	400dac <pm_set_last_latch_tick>
  400edc:	e7e5      	b.n	400eaa <SysTick_Handler+0x1e>
  400ede:	bf00      	nop
  400ee0:	40040000 	.word	0x40040000

00400ee4 <HAL_AssertFailed>:
  400ee4:	2300      	movs	r3, #0
  400ee6:	b507      	push	{r0, r1, r2, lr}
  400ee8:	f44f 721a 	mov.w	r2, #616	@ 0x268
  400eec:	4905      	ldr	r1, [pc, #20]	@ (400f04 <HAL_AssertFailed+0x20>)
  400eee:	4806      	ldr	r0, [pc, #24]	@ (400f08 <HAL_AssertFailed+0x24>)
  400ef0:	9301      	str	r3, [sp, #4]
  400ef2:	f450 fa33 	bl	5135c <rt_assert_handler>
  400ef6:	9b01      	ldr	r3, [sp, #4]
  400ef8:	2b00      	cmp	r3, #0
  400efa:	d0fc      	beq.n	400ef6 <HAL_AssertFailed+0x12>
  400efc:	b003      	add	sp, #12
  400efe:	f85d fb04 	ldr.w	pc, [sp], #4
  400f02:	bf00      	nop
  400f04:	00401434 	.word	0x00401434
  400f08:	00401354 	.word	0x00401354

00400f0c <rt_hw_preboard_init>:
  400f0c:	4770      	bx	lr
	...

00400f10 <rt_hw_board_init>:
  400f10:	b508      	push	{r3, lr}
  400f12:	f7ff fffb 	bl	400f0c <rt_hw_preboard_init>
  400f16:	f7ff f9e6 	bl	4002e6 <HAL_Init>
  400f1a:	4808      	ldr	r0, [pc, #32]	@ (400f3c <rt_hw_board_init+0x2c>)
  400f1c:	f454 ff46 	bl	55dac <rt_thread_inited_sethook>
  400f20:	f7ff f937 	bl	400192 <SystemClock_Config>
  400f24:	f451 fbb8 	bl	52698 <rt_hw_systick_init>
  400f28:	f451 fc00 	bl	5272c <rt_hw_watchdog_init>
  400f2c:	4904      	ldr	r1, [pc, #16]	@ (400f40 <rt_hw_board_init+0x30>)
  400f2e:	4805      	ldr	r0, [pc, #20]	@ (400f44 <rt_hw_board_init+0x34>)
  400f30:	f454 fb1a 	bl	55568 <rt_system_heap_init>
  400f34:	e8bd 4008 	ldmia.w	sp!, {r3, lr}
  400f38:	f000 b80e 	b.w	400f58 <rt_components_board_init>
  400f3c:	00400e41 	.word	0x00400e41
  400f40:	20405c00 	.word	0x20405c00
  400f44:	20401d00 	.word	0x20401d00

00400f48 <rti_start>:
  400f48:	2000      	movs	r0, #0
  400f4a:	4770      	bx	lr

00400f4c <rti_board_start>:
  400f4c:	2000      	movs	r0, #0
  400f4e:	4770      	bx	lr

00400f50 <rti_board_end>:
  400f50:	2000      	movs	r0, #0
  400f52:	4770      	bx	lr

00400f54 <rti_end>:
  400f54:	2000      	movs	r0, #0
  400f56:	4770      	bx	lr

00400f58 <rt_components_board_init>:
  400f58:	b538      	push	{r3, r4, r5, lr}
  400f5a:	4c04      	ldr	r4, [pc, #16]	@ (400f6c <rt_components_board_init+0x14>)
  400f5c:	4d04      	ldr	r5, [pc, #16]	@ (400f70 <rt_components_board_init+0x18>)
  400f5e:	42ac      	cmp	r4, r5
  400f60:	d300      	bcc.n	400f64 <rt_components_board_init+0xc>
  400f62:	bd38      	pop	{r3, r4, r5, pc}
  400f64:	f854 3b04 	ldr.w	r3, [r4], #4
  400f68:	4798      	blx	r3
  400f6a:	e7f8      	b.n	400f5e <rt_components_board_init+0x6>
  400f6c:	0040156c 	.word	0x0040156c
  400f70:	00401570 	.word	0x00401570

00400f74 <rt_components_init>:
  400f74:	b538      	push	{r3, r4, r5, lr}
  400f76:	4c05      	ldr	r4, [pc, #20]	@ (400f8c <rt_components_init+0x18>)
  400f78:	4d05      	ldr	r5, [pc, #20]	@ (400f90 <rt_components_init+0x1c>)
  400f7a:	42ac      	cmp	r4, r5
  400f7c:	d300      	bcc.n	400f80 <rt_components_init+0xc>
  400f7e:	bd38      	pop	{r3, r4, r5, pc}
  400f80:	f854 3b04 	ldr.w	r3, [r4], #4
  400f84:	2b00      	cmp	r3, #0
  400f86:	d0f8      	beq.n	400f7a <rt_components_init+0x6>
  400f88:	4798      	blx	r3
  400f8a:	e7f6      	b.n	400f7a <rt_components_init+0x6>
  400f8c:	00401570 	.word	0x00401570
  400f90:	00401590 	.word	0x00401590

00400f94 <main_thread_entry>:
  400f94:	b513      	push	{r0, r1, r4, lr}
  400f96:	2402      	movs	r4, #2
  400f98:	f88d 4006 	strb.w	r4, [sp, #6]
  400f9c:	f454 ff56 	bl	55e4c <rt_thread_self>
  400fa0:	f890 3035 	ldrb.w	r3, [r0, #53]	@ 0x35
  400fa4:	f88d 3007 	strb.w	r3, [sp, #7]
  400fa8:	f454 ff50 	bl	55e4c <rt_thread_self>
  400fac:	4621      	mov	r1, r4
  400fae:	f10d 0206 	add.w	r2, sp, #6
  400fb2:	f454 fc5f 	bl	55874 <rt_thread_control>
  400fb6:	f7ff ffdd 	bl	400f74 <rt_components_init>
  400fba:	f454 ff47 	bl	55e4c <rt_thread_self>
  400fbe:	4621      	mov	r1, r4
  400fc0:	f10d 0207 	add.w	r2, sp, #7
  400fc4:	f454 fc56 	bl	55874 <rt_thread_control>
  400fc8:	f7ff f91c 	bl	400204 <main>
  400fcc:	b002      	add	sp, #8
  400fce:	bd10      	pop	{r4, pc}

00400fd0 <pre_main>:
  400fd0:	4770      	bx	lr
	...

00400fd4 <rt_application_init>:
  400fd4:	2302      	movs	r3, #2
  400fd6:	2214      	movs	r2, #20
  400fd8:	b513      	push	{r0, r1, r4, lr}
  400fda:	490b      	ldr	r1, [pc, #44]	@ (401008 <rt_application_init+0x34>)
  400fdc:	e9cd 3200 	strd	r3, r2, [sp]
  400fe0:	480a      	ldr	r0, [pc, #40]	@ (40100c <rt_application_init+0x38>)
  400fe2:	f44f 6380 	mov.w	r3, #1024	@ 0x400
  400fe6:	2200      	movs	r2, #0
  400fe8:	f454 fc8c 	bl	55904 <rt_thread_create>
  400fec:	4604      	mov	r4, r0
  400fee:	b928      	cbnz	r0, 400ffc <rt_application_init+0x28>
  400ff0:	f240 1261 	movw	r2, #353	@ 0x161
  400ff4:	4906      	ldr	r1, [pc, #24]	@ (401010 <rt_application_init+0x3c>)
  400ff6:	4807      	ldr	r0, [pc, #28]	@ (401014 <rt_application_init+0x40>)
  400ff8:	f450 f9b0 	bl	5135c <rt_assert_handler>
  400ffc:	4620      	mov	r0, r4
  400ffe:	b002      	add	sp, #8
  401000:	e8bd 4010 	ldmia.w	sp!, {r4, lr}
  401004:	f454 bfc0 	b.w	55f88 <rt_thread_startup>
  401008:	00400f95 	.word	0x00400f95
  40100c:	0040138d 	.word	0x0040138d
  401010:	00401445 	.word	0x00401445
  401014:	00401392 	.word	0x00401392

00401018 <rtthread_startup>:
  401018:	b508      	push	{r3, lr}
  40101a:	f7ff f3df 	bl	7dc <rt_hw_interrupt_disable>
  40101e:	f7ff fe05 	bl	400c2c <rt_application_init_power_on_mode>
  401022:	f7ff ff75 	bl	400f10 <rt_hw_board_init>
  401026:	f7ff fe07 	bl	400c38 <SystemPowerOnModeGet>
  40102a:	b908      	cbnz	r0, 401030 <rtthread_startup+0x18>
  40102c:	f454 fa01 	bl	55432 <rt_show_version>
  401030:	f454 fc16 	bl	55860 <rt_system_timer_init>
  401034:	f454 fbea 	bl	5580c <rt_system_scheduler_init>
  401038:	f7ff ffcc 	bl	400fd4 <rt_application_init>
  40103c:	f454 fc18 	bl	55870 <rt_system_timer_thread_init>
  401040:	f000 f81e 	bl	401080 <rt_thread_idle_init>
  401044:	f454 fbf8 	bl	55838 <rt_system_scheduler_start>
  401048:	2000      	movs	r0, #0
  40104a:	bd08      	pop	{r3, pc}

0040104c <entry>:
  40104c:	b508      	push	{r3, lr}
  40104e:	f7ff ffbf 	bl	400fd0 <pre_main>
  401052:	f7ff ffe1 	bl	401018 <rtthread_startup>
  401056:	2000      	movs	r0, #0
  401058:	bd08      	pop	{r3, pc}
	...

0040105c <rt_thread_idle_entry>:
  40105c:	b538      	push	{r3, r4, r5, lr}
  40105e:	2400      	movs	r4, #0
  401060:	4d06      	ldr	r5, [pc, #24]	@ (40107c <rt_thread_idle_entry+0x20>)
  401062:	f855 3b04 	ldr.w	r3, [r5], #4
  401066:	b103      	cbz	r3, 40106a <rt_thread_idle_entry+0xe>
  401068:	4798      	blx	r3
  40106a:	3401      	adds	r4, #1
  40106c:	2c04      	cmp	r4, #4
  40106e:	d1f8      	bne.n	401062 <rt_thread_idle_entry+0x6>
  401070:	f454 fdc8 	bl	55c04 <rt_thread_idle_excute>
  401074:	f454 fb06 	bl	55684 <rt_system_power_manager>
  401078:	e7f1      	b.n	40105e <rt_thread_idle_entry+0x2>
  40107a:	bf00      	nop
  40107c:	2040efec 	.word	0x2040efec

00401080 <rt_thread_idle_init>:
  401080:	b51f      	push	{r0, r1, r2, r3, r4, lr}
  401082:	2307      	movs	r3, #7
  401084:	2220      	movs	r2, #32
  401086:	e9cd 3202 	strd	r3, r2, [sp, #8]
  40108a:	f44f 7300 	mov.w	r3, #512	@ 0x200
  40108e:	9301      	str	r3, [sp, #4]
  401090:	4b06      	ldr	r3, [pc, #24]	@ (4010ac <rt_thread_idle_init+0x2c>)
  401092:	4a07      	ldr	r2, [pc, #28]	@ (4010b0 <rt_thread_idle_init+0x30>)
  401094:	9300      	str	r3, [sp, #0]
  401096:	4907      	ldr	r1, [pc, #28]	@ (4010b4 <rt_thread_idle_init+0x34>)
  401098:	2300      	movs	r3, #0
  40109a:	4807      	ldr	r0, [pc, #28]	@ (4010b8 <rt_thread_idle_init+0x38>)
  40109c:	f454 fe4a 	bl	55d34 <rt_thread_init>
  4010a0:	4805      	ldr	r0, [pc, #20]	@ (4010b8 <rt_thread_idle_init+0x38>)
  4010a2:	b005      	add	sp, #20
  4010a4:	f85d eb04 	ldr.w	lr, [sp], #4
  4010a8:	f454 bf6e 	b.w	55f88 <rt_thread_startup>
  4010ac:	20401b00 	.word	0x20401b00
  4010b0:	0040105d 	.word	0x0040105d
  4010b4:	004013a1 	.word	0x004013a1
  4010b8:	2040ef70 	.word	0x2040ef70

004010bc <rt_hw_set_stack_limit>:
  4010bc:	4770      	bx	lr
  4010be:	0000      	movs	r0, r0
  4010c0:	f3ef 8010 	mrs	r0, PRIMASK
  4010c4:	b672      	cpsid	i
  4010c6:	4770      	bx	lr
  4010c8:	f380 8810 	msr	PRIMASK, r0
  4010cc:	4770      	bx	lr
  4010ce:	bf40      	sev
  4010d0:	4a5f      	ldr	r2, [pc, #380]	@ (401250 <rt_hw_fatal_error+0x44>)
  4010d2:	6813      	ldr	r3, [r2, #0]
  4010d4:	2b01      	cmp	r3, #1
  4010d6:	d004      	beq.n	4010e2 <_reswitch>
  4010d8:	f04f 0301 	mov.w	r3, #1
  4010dc:	6013      	str	r3, [r2, #0]
  4010de:	4a5d      	ldr	r2, [pc, #372]	@ (401254 <rt_hw_fatal_error+0x48>)
  4010e0:	6010      	str	r0, [r2, #0]

004010e2 <_reswitch>:
  4010e2:	4a5d      	ldr	r2, [pc, #372]	@ (401258 <rt_hw_fatal_error+0x4c>)
  4010e4:	6011      	str	r1, [r2, #0]
  4010e6:	485d      	ldr	r0, [pc, #372]	@ (40125c <rt_hw_fatal_error+0x50>)
  4010e8:	f04f 5180 	mov.w	r1, #268435456	@ 0x10000000
  4010ec:	6001      	str	r1, [r0, #0]
  4010ee:	4770      	bx	lr
  4010f0:	f3ef 8210 	mrs	r2, PRIMASK
  4010f4:	b672      	cpsid	i
  4010f6:	4856      	ldr	r0, [pc, #344]	@ (401250 <rt_hw_fatal_error+0x44>)
  4010f8:	6801      	ldr	r1, [r0, #0]
  4010fa:	b1c9      	cbz	r1, 401130 <pendsv_exit>
  4010fc:	f04f 0100 	mov.w	r1, #0
  401100:	6001      	str	r1, [r0, #0]
  401102:	4854      	ldr	r0, [pc, #336]	@ (401254 <rt_hw_fatal_error+0x48>)
  401104:	6801      	ldr	r1, [r0, #0]
  401106:	b149      	cbz	r1, 40111c <switch_to_thread>
  401108:	f3ef 8109 	mrs	r1, PSP
  40110c:	e921 0ff0 	stmdb	r1!, {r4, r5, r6, r7, r8, r9, sl, fp}
  401110:	f3ef 840b 	mrs	r4, PSPLIM
  401114:	f841 4d04 	str.w	r4, [r1, #-4]!
  401118:	6800      	ldr	r0, [r0, #0]
  40111a:	6001      	str	r1, [r0, #0]

0040111c <switch_to_thread>:
  40111c:	494e      	ldr	r1, [pc, #312]	@ (401258 <rt_hw_fatal_error+0x4c>)
  40111e:	6809      	ldr	r1, [r1, #0]
  401120:	6809      	ldr	r1, [r1, #0]
  401122:	c910      	ldmia	r1!, {r4}
  401124:	f384 880b 	msr	PSPLIM, r4
  401128:	e8b1 0ff0 	ldmia.w	r1!, {r4, r5, r6, r7, r8, r9, sl, fp}
  40112c:	f381 8809 	msr	PSP, r1

00401130 <pendsv_exit>:
  401130:	f382 8810 	msr	PRIMASK, r2
  401134:	f04e 0e04 	orr.w	lr, lr, #4
  401138:	4770      	bx	lr
  40113a:	4849      	ldr	r0, [pc, #292]	@ (401260 <rt_hw_fatal_error+0x54>)
  40113c:	f44f 017f 	mov.w	r1, #16711680	@ 0xff0000
  401140:	f8d0 2000 	ldr.w	r2, [r0]
  401144:	ea41 0102 	orr.w	r1, r1, r2
  401148:	6001      	str	r1, [r0, #0]
  40114a:	4770      	bx	lr
  40114c:	4942      	ldr	r1, [pc, #264]	@ (401258 <rt_hw_fatal_error+0x4c>)
  40114e:	6008      	str	r0, [r1, #0]
  401150:	4940      	ldr	r1, [pc, #256]	@ (401254 <rt_hw_fatal_error+0x48>)
  401152:	f04f 0000 	mov.w	r0, #0
  401156:	6008      	str	r0, [r1, #0]
  401158:	493d      	ldr	r1, [pc, #244]	@ (401250 <rt_hw_fatal_error+0x44>)
  40115a:	f04f 0001 	mov.w	r0, #1
  40115e:	6008      	str	r0, [r1, #0]
  401160:	483f      	ldr	r0, [pc, #252]	@ (401260 <rt_hw_fatal_error+0x54>)
  401162:	f44f 017f 	mov.w	r1, #16711680	@ 0xff0000
  401166:	f8d0 2000 	ldr.w	r2, [r0]
  40116a:	ea41 0102 	orr.w	r1, r1, r2
  40116e:	6001      	str	r1, [r0, #0]
  401170:	483a      	ldr	r0, [pc, #232]	@ (40125c <rt_hw_fatal_error+0x50>)
  401172:	f04f 5180 	mov.w	r1, #268435456	@ 0x10000000
  401176:	6001      	str	r1, [r0, #0]
  401178:	483a      	ldr	r0, [pc, #232]	@ (401264 <rt_hw_fatal_error+0x58>)
  40117a:	6800      	ldr	r0, [r0, #0]
  40117c:	6800      	ldr	r0, [r0, #0]
  40117e:	bf00      	nop
  401180:	f380 8808 	msr	MSP, r0
  401184:	b661      	cpsie	f
  401186:	b662      	cpsie	i
  401188:	4770      	bx	lr
  40118a:	bf00      	nop
  40118c:	bf20      	wfe
  40118e:	4770      	bx	lr
  401190:	f3ef 8008 	mrs	r0, MSP
  401194:	f01e 0f04 	tst.w	lr, #4
  401198:	d001      	beq.n	40119e <_get_sp_done>
  40119a:	f3ef 8009 	mrs	r0, PSP

0040119e <_get_sp_done>:
  40119e:	e920 0ff0 	stmdb	r0!, {r4, r5, r6, r7, r8, r9, sl, fp}
  4011a2:	f3ef 840b 	mrs	r4, PSPLIM
  4011a6:	f840 4d04 	str.w	r4, [r0, #-4]!
  4011aa:	f840 ed04 	str.w	lr, [r0, #-4]!
  4011ae:	f01e 0f04 	tst.w	lr, #4
  4011b2:	d002      	beq.n	4011ba <_update_msp>
  4011b4:	f380 8809 	msr	PSP, r0
  4011b8:	e001      	b.n	4011be <_update_done>

004011ba <_update_msp>:
  4011ba:	f380 8808 	msr	MSP, r0

004011be <_update_done>:
  4011be:	b500      	push	{lr}
  4011c0:	f451 fa2d 	bl	5261e <rt_hw_hard_fault_exception>
  4011c4:	f85d eb04 	ldr.w	lr, [sp], #4
  4011c8:	f04e 0e04 	orr.w	lr, lr, #4
  4011cc:	4770      	bx	lr
  4011ce:	f3ef 8008 	mrs	r0, MSP
  4011d2:	f01e 0f04 	tst.w	lr, #4
  4011d6:	d001      	beq.n	4011dc <_mm_get_sp_done>
  4011d8:	f3ef 8009 	mrs	r0, PSP

004011dc <_mm_get_sp_done>:
  4011dc:	e920 0ff0 	stmdb	r0!, {r4, r5, r6, r7, r8, r9, sl, fp}
  4011e0:	f3ef 840b 	mrs	r4, PSPLIM
  4011e4:	f840 4d04 	str.w	r4, [r0, #-4]!
  4011e8:	f840 ed04 	str.w	lr, [r0, #-4]!
  4011ec:	f01e 0f04 	tst.w	lr, #4
  4011f0:	d002      	beq.n	4011f8 <_mm_update_msp>
  4011f2:	f380 8809 	msr	PSP, r0
  4011f6:	e001      	b.n	4011fc <_mm_update_done>

004011f8 <_mm_update_msp>:
  4011f8:	f380 8808 	msr	MSP, r0

004011fc <_mm_update_done>:
  4011fc:	b500      	push	{lr}
  4011fe:	f451 fa11 	bl	52624 <rt_hw_mem_manage_exception>
  401202:	f85d eb04 	ldr.w	lr, [sp], #4
  401206:	f04e 0e04 	orr.w	lr, lr, #4
  40120a:	4770      	bx	lr

0040120c <rt_hw_fatal_error>:
  40120c:	b410      	push	{r4}
  40120e:	f3ef 8403 	mrs	r4, PSR
  401212:	b410      	push	{r4}
  401214:	467c      	mov	r4, pc
  401216:	b410      	push	{r4}
  401218:	b500      	push	{lr}
  40121a:	f84d cd04 	str.w	ip, [sp, #-4]!
  40121e:	b40f      	push	{r0, r1, r2, r3}
  401220:	9c08      	ldr	r4, [sp, #32]
  401222:	e92d 0ff0 	stmdb	sp!, {r4, r5, r6, r7, r8, r9, sl, fp}
  401226:	f3ef 840b 	mrs	r4, PSPLIM
  40122a:	b410      	push	{r4}
  40122c:	4668      	mov	r0, sp
  40122e:	f451 f9b5 	bl	5259c <rt_hw_do_fatal_error>
  401232:	bc10      	pop	{r4}
  401234:	f384 880b 	msr	PSPLIM, r4
  401238:	e8bd 0ff0 	ldmia.w	sp!, {r4, r5, r6, r7, r8, r9, sl, fp}
  40123c:	bc0f      	pop	{r0, r1, r2, r3}
  40123e:	f85d cb04 	ldr.w	ip, [sp], #4
  401242:	f85d eb04 	ldr.w	lr, [sp], #4
  401246:	bc10      	pop	{r4}
  401248:	bc10      	pop	{r4}
  40124a:	bc10      	pop	{r4}
  40124c:	e7fe      	b.n	40124c <rt_hw_fatal_error+0x40>
  40124e:	0000      	.short	0x0000
  401250:	2040f8a4 	.word	0x2040f8a4
  401254:	2040f874 	.word	0x2040f874
  401258:	2040f878 	.word	0x2040f878
  40125c:	e000ed04 	.word	0xe000ed04
  401260:	e000ed20 	.word	0xe000ed20
  401264:	e000ed08 	.word	0xe000ed08

00401268 <memset>:
  401268:	4402      	add	r2, r0
  40126a:	4603      	mov	r3, r0
  40126c:	4293      	cmp	r3, r2
  40126e:	d100      	bne.n	401272 <memset+0xa>
  401270:	4770      	bx	lr
  401272:	f803 1b01 	strb.w	r1, [r3], #1
  401276:	e7f9      	b.n	40126c <memset+0x4>
  401278:	4f5c3a45 	.word	0x4f5c3a45
  40127c:	536e6570 	.word	0x536e6570
  401280:	696c4669 	.word	0x696c4669
  401284:	6669735c 	.word	0x6669735c
  401288:	732d696c 	.word	0x732d696c
  40128c:	645c6b64 	.word	0x645c6b64
  401290:	65766972 	.word	0x65766972
  401294:	685c7372 	.word	0x685c7372
  401298:	625c6c61 	.word	0x625c6c61
  40129c:	685f3066 	.word	0x685f3066
  4012a0:	6d5f6c61 	.word	0x6d5f6c61
  4012a4:	626c6961 	.word	0x626c6961
  4012a8:	632e786f 	.word	0x632e786f
  4012ac:	5c3a4500 	.word	0x5c3a4500
  4012b0:	6e65704f 	.word	0x6e65704f
  4012b4:	6c466953 	.word	0x6c466953
  4012b8:	69735c69 	.word	0x69735c69
  4012bc:	2d696c66 	.word	0x2d696c66
  4012c0:	5c6b6473 	.word	0x5c6b6473
  4012c4:	76697264 	.word	0x76697264
  4012c8:	5c737265 	.word	0x5c737265
  4012cc:	5c6c6168 	.word	0x5c6c6168
  4012d0:	5f306662 	.word	0x5f306662
  4012d4:	5f6c6168 	.word	0x5f6c6168
  4012d8:	6d6e6970 	.word	0x6d6e6970
  4012dc:	632e7875 	.word	0x632e7875
  4012e0:	5c3a4500 	.word	0x5c3a4500
  4012e4:	6e65704f 	.word	0x6e65704f
  4012e8:	6c466953 	.word	0x6c466953
  4012ec:	69735c69 	.word	0x69735c69
  4012f0:	2d696c66 	.word	0x2d696c66
  4012f4:	5c6b6473 	.word	0x5c6b6473
  4012f8:	76697264 	.word	0x76697264
  4012fc:	5c737265 	.word	0x5c737265
  401300:	5c6c6168 	.word	0x5c6c6168
  401304:	5f306662 	.word	0x5f306662
  401308:	5f6c6168 	.word	0x5f6c6168
  40130c:	2e637470 	.word	0x2e637470
  401310:	3a450063 	.word	0x3a450063
  401314:	65704f5c 	.word	0x65704f5c
  401318:	4669536e 	.word	0x4669536e
  40131c:	735c696c 	.word	0x735c696c
  401320:	696c6669 	.word	0x696c6669
  401324:	6b64732d 	.word	0x6b64732d
  401328:	6972645c 	.word	0x6972645c
  40132c:	73726576 	.word	0x73726576
  401330:	6c61685c 	.word	0x6c61685c
  401334:	3066625c 	.word	0x3066625c
  401338:	6c61685f 	.word	0x6c61685f
  40133c:	6363725f 	.word	0x6363725f
  401340:	6300632e 	.word	0x6300632e
  401344:	626c6c61 	.word	0x626c6c61
  401348:	206b6361 	.word	0x206b6361
  40134c:	4e203d21 	.word	0x4e203d21
  401350:	004c4c55 	.word	0x004c4c55
  401354:	6c740030 	.word	0x6c740030
  401358:	5f545200 	.word	0x5f545200
  40135c:	534c4146 	.word	0x534c4146
  401360:	5f710045 	.word	0x5f710045
  401364:	20786469 	.word	0x20786469
  401368:	5049203c 	.word	0x5049203c
  40136c:	57485f43 	.word	0x57485f43
  401370:	4555515f 	.word	0x4555515f
  401374:	4e5f4555 	.word	0x4e5f4555
  401378:	48004d55 	.word	0x48004d55
  40137c:	4f5f4c41 	.word	0x4f5f4c41
  401380:	3d3d204b 	.word	0x3d3d204b
  401384:	72726520 	.word	0x72726520
  401388:	6e697000 	.word	0x6e697000
  40138c:	69616d00 	.word	0x69616d00
  401390:	6974006e 	.word	0x6974006e
  401394:	3d212064 	.word	0x3d212064
  401398:	5f545220 	.word	0x5f545220
  40139c:	4c4c554e 	.word	0x4c4c554e
  4013a0:	64697400 	.word	0x64697400
  4013a4:	0000656c 	.word	0x0000656c

004013a8 <g_ble_mac_pm_ops>:
  4013a8:	004008d5 00000000 00000000              ..@.........

004013b4 <__FUNCTION__.0>:
  4013b4:	74726f70 6e6f635f 00676966              port_config.

004013c0 <__FUNCTION__.3>:
  4013c0:	5f6d6f72 74726f70 7465675f               rom_port_get.

004013cd <__FUNCTION__.0>:
  4013cd:	5f637470 666e6f63                        ptc_config.

004013d8 <__FUNCTION__.0>:
  4013d8:	75706368 70636c32 6f6e5f75 69666974     hcpu2lcpu_notifi
  4013e8:	69746163 635f6e6f 626c6c61 006b6361     cation_callback.

004013f8 <__FUNCTION__.1>:
  4013f8:	5f474244 67697254 5f726567 48515249     DBG_Trigger_IRQH
  401408:	6c646e61                                 andler.

0040140f <__FUNCTION__.2>:
  40140f:	705f6d70 725f6e69 6f747365 00006572     pm_pin_restore..
	...

00401420 <sifli_pm_op>:
  401420:	00400c01 00400bff 00000000              ..@...@.....

0040142c <pm_policy>:
  40142c:	0000000a 00000003                       ........

00401434 <__FUNCTION__.0>:
  401434:	5f4c4148 65737341 61467472 64656c69     HAL_AssertFailed
	...

00401445 <__FUNCTION__.0>:
  401445:	615f7472 696c7070 69746163 695f6e6f     rt_application_i
  401455:	0074696e                                 nit....

0040145c <HAL_PIN_Restore>:
  40145c:	b510      	push	{r4, lr}
  40145e:	4604      	mov	r4, r0
  401460:	b920      	cbnz	r0, 40146c <HAL_PIN_Restore+0x10>
  401462:	f640 0181 	movw	r1, #2177	@ 0x881
  401466:	480a      	ldr	r0, [pc, #40]	@ (401490 <HAL_PIN_Restore+0x34>)
  401468:	f7ff fd3c 	bl	400ee4 <HAL_AssertFailed>
  40146c:	6822      	ldr	r2, [r4, #0]
  40146e:	4b09      	ldr	r3, [pc, #36]	@ (401494 <HAL_PIN_Restore+0x38>)
  401470:	2000      	movs	r0, #0
  401472:	601a      	str	r2, [r3, #0]
  401474:	6862      	ldr	r2, [r4, #4]
  401476:	605a      	str	r2, [r3, #4]
  401478:	68a2      	ldr	r2, [r4, #8]
  40147a:	609a      	str	r2, [r3, #8]
  40147c:	68e2      	ldr	r2, [r4, #12]
  40147e:	60da      	str	r2, [r3, #12]
  401480:	6922      	ldr	r2, [r4, #16]
  401482:	f503 4340 	add.w	r3, r3, #49152	@ 0xc000
  401486:	639a      	str	r2, [r3, #56]	@ 0x38
  401488:	6962      	ldr	r2, [r4, #20]
  40148a:	63da      	str	r2, [r3, #60]	@ 0x3c
  40148c:	bd10      	pop	{r4, pc}
  40148e:	bf00      	nop
  401490:	004012ad 	.word	0x004012ad
  401494:	40003000 	.word	0x40003000

00401498 <sifli_pm_run>:
  401498:	4770      	bx	lr

0040149a <sifli_enter_idle>:
  40149a:	4770      	bx	lr

0040149c <pm_pin_restore>:
  40149c:	b508      	push	{r3, lr}
  40149e:	480c      	ldr	r0, [pc, #48]	@ (4014d0 <pm_pin_restore+0x34>)
  4014a0:	f7ff ffdc 	bl	40145c <HAL_PIN_Restore>
  4014a4:	b128      	cbz	r0, 4014b2 <pm_pin_restore+0x16>
  4014a6:	f240 12a7 	movw	r2, #423	@ 0x1a7
  4014aa:	490a      	ldr	r1, [pc, #40]	@ (4014d4 <pm_pin_restore+0x38>)
  4014ac:	480a      	ldr	r0, [pc, #40]	@ (4014d8 <pm_pin_restore+0x3c>)
  4014ae:	f44f ff55 	bl	5135c <rt_assert_handler>
  4014b2:	2202      	movs	r2, #2
  4014b4:	4909      	ldr	r1, [pc, #36]	@ (4014dc <pm_pin_restore+0x40>)
  4014b6:	480a      	ldr	r0, [pc, #40]	@ (4014e0 <pm_pin_restore+0x44>)
  4014b8:	f7fe ff5e 	bl	400378 <HAL_GPIO_Restore>
  4014bc:	b138      	cbz	r0, 4014ce <pm_pin_restore+0x32>
  4014be:	e8bd 4008 	ldmia.w	sp!, {r3, lr}
  4014c2:	f240 12ab 	movw	r2, #427	@ 0x1ab
  4014c6:	4903      	ldr	r1, [pc, #12]	@ (4014d4 <pm_pin_restore+0x38>)
  4014c8:	4803      	ldr	r0, [pc, #12]	@ (4014d8 <pm_pin_restore+0x3c>)
  4014ca:	f44f bf47 	b.w	5135c <rt_assert_handler>
  4014ce:	bd08      	pop	{r3, pc}
  4014d0:	20401a7c 	.word	0x20401a7c
  4014d4:	0040140f 	.word	0x0040140f
  4014d8:	0040137b 	.word	0x0040137b
  4014dc:	20401a94 	.word	0x20401a94
  4014e0:	40080000 	.word	0x40080000

004014e4 <SystemPowerOnInitLCPU>:
  4014e4:	b538      	push	{r3, r4, r5, lr}
  4014e6:	4c16      	ldr	r4, [pc, #88]	@ (401540 <SystemPowerOnInitLCPU+0x5c>)
  4014e8:	6823      	ldr	r3, [r4, #0]
  4014ea:	f003 0303 	and.w	r3, r3, #3
  4014ee:	2b03      	cmp	r3, #3
  4014f0:	4b14      	ldr	r3, [pc, #80]	@ (401544 <SystemPowerOnInitLCPU+0x60>)
  4014f2:	d002      	beq.n	4014fa <SystemPowerOnInitLCPU+0x16>
  4014f4:	2200      	movs	r2, #0
  4014f6:	701a      	strb	r2, [r3, #0]
  4014f8:	bd38      	pop	{r3, r4, r5, pc}
  4014fa:	2501      	movs	r5, #1
  4014fc:	701d      	strb	r5, [r3, #0]
  4014fe:	f455 fc01 	bl	56d04 <rt_wdt_restore>
  401502:	4a11      	ldr	r2, [pc, #68]	@ (401548 <SystemPowerOnInitLCPU+0x64>)
  401504:	6913      	ldr	r3, [r2, #16]
  401506:	f043 5300 	orr.w	r3, r3, #536870912	@ 0x20000000
  40150a:	6113      	str	r3, [r2, #16]
  40150c:	6c63      	ldr	r3, [r4, #68]	@ 0x44
  40150e:	f023 0302 	bic.w	r3, r3, #2
  401512:	6463      	str	r3, [r4, #68]	@ 0x44
  401514:	f7ff ffc2 	bl	40149c <pm_pin_restore>
  401518:	6c63      	ldr	r3, [r4, #68]	@ 0x44
  40151a:	f023 0301 	bic.w	r3, r3, #1
  40151e:	6463      	str	r3, [r4, #68]	@ 0x44
  401520:	f7fe fee1 	bl	4002e6 <HAL_Init>
  401524:	f7ff f15a 	bl	7dc <rt_hw_interrupt_disable>
  401528:	4b08      	ldr	r3, [pc, #32]	@ (40154c <SystemPowerOnInitLCPU+0x68>)
  40152a:	601d      	str	r5, [r3, #0]
  40152c:	f7fe fe31 	bl	400192 <SystemClock_Config>
  401530:	f451 f8b2 	bl	52698 <rt_hw_systick_init>
  401534:	f7ff f18f 	bl	856 <rt_hw_cfg_pendsv_pri>
  401538:	f44f fba0 	bl	50c7c <restore_context>
  40153c:	e7dc      	b.n	4014f8 <SystemPowerOnInitLCPU+0x14>
  40153e:	bf00      	nop
  401540:	40040000 	.word	0x40040000
  401544:	2040fd54 	.word	0x2040fd54
  401548:	4000f000 	.word	0x4000f000
  40154c:	20401aec 	.word	0x20401aec

00401550 <_init>:
  401550:	b5f8      	push	{r3, r4, r5, r6, r7, lr}
  401552:	bf00      	nop
  401554:	bcf8      	pop	{r3, r4, r5, r6, r7}
  401556:	bc08      	pop	{r3}
  401558:	469e      	mov	lr, r3
  40155a:	4770      	bx	lr

0040155c <_fini>:
  40155c:	b5f8      	push	{r3, r4, r5, r6, r7, lr}
  40155e:	bf00      	nop
  401560:	bcf8      	pop	{r3, r4, r5, r6, r7}
  401562:	bc08      	pop	{r3}
  401564:	469e      	mov	lr, r3
  401566:	4770      	bx	lr

00401568 <__rt_init_rti_start>:
  401568:	0f49 0040                                   I.@.

0040156c <__rt_init_rti_board_start>:
  40156c:	0f4d 0040                                   M.@.

00401570 <__rt_init_rti_board_end>:
  401570:	0f51 0040                                   Q.@.

00401574 <__rt_init_low_power_init>:
  401574:	0c91 0040                                   ..@.

00401578 <__rt_init_libc_system_init>:
  401578:	a6e1 0002                                   ....

0040157c <__rt_init_rc10k_cal_init>:
  40157c:	01c5 0040                                   ..@.

00401580 <__rt_init_sys_init_lh_bt_audio_queue>:
  401580:	aced 0005                                   ....

00401584 <__rt_init_bt_audiopath_init>:
  401584:	07c1 0040                                   ..@.

00401588 <__rt_init_bluetooth_init>:
  401588:	0851 0040                                   Q.@.

0040158c <__rt_init_sys_init_debug_trigger>:
  40158c:	0b69 0040                                   i.@.

00401590 <__rt_init_rti_end>:
  401590:	0f55 0040                                   U.@.

00401594 <__EH_FRAME_BEGIN__>:
  401594:	0000 0000                                   ....
