%macro export_func 1
   global _%1
   _%1:
%endmacro
%define SAMPLE_RATE	44100
%define MAX_INSTRUMENTS	7
%define MAX_VOICES 1
%define HLD 1
%define BPM 140.000000
%define MAX_PATTERNS 18
%define PATTERN_SIZE_SHIFT 5
%define PATTERN_SIZE (1 << PATTERN_SIZE_SHIFT)
%define	MAX_TICKS (MAX_PATTERNS*PATTERN_SIZE)
%define	SAMPLES_PER_TICK 4725
%define DEF_LFO_NORMALIZE 0.0000529101
%define	MAX_SAMPLES	(SAMPLES_PER_TICK*MAX_TICKS)
;%define 	GO4K_USE_16BIT_OUTPUT
;%define 	GO4K_USE_GROOVE_PATTERN
%define 	GO4K_USE_ENVELOPE_RECORDINGS
%define 	GO4K_USE_NOTE_RECORDINGS
%define 	GO4K_CLIP_OUTPUT
%define 	GO4K_USE_DLL
%define 	GO4K_USE_GLOBAL_DLL
%define 	GO4K_USE_ENV_CHECK
%define 	GO4K_USE_ENV_MOD_GM
%define 	GO4K_USE_VCO_CHECK
%define 	GO4K_USE_VCO_PHASE_OFFSET
%define 	GO4K_USE_VCO_SHAPE
%define 	GO4K_USE_VCO_MOD_PM
%define 	GO4K_USE_VCF_CHECK
%define 	GO4K_USE_VCF_HIGH
%define 	GO4K_USE_VCF_BAND
%define 	GO4K_USE_VCF_PEAK
%define 	GO4K_USE_DST_CHECK
%define		GO4K_USE_DLL_NOTE_SYNC
%define		GO4K_USE_DLL_CHORUS_CLAMP
%define 	GO4K_USE_DLL_DAMP
%define 	GO4K_USE_DLL_DC_FILTER
%define 	GO4K_USE_FSTG_CHECK
%define		GO4K_USE_WAVESHAPER_CLIP
%define	MAX_DELAY			65536
%define MAX_UNITS			64
%define	MAX_UNIT_SLOTS	    16
%define GO4K_BEGIN_CMDDEF(def_name)
%define GO4K_END_CMDDEF db 0
%define GO4K_BEGIN_PARAMDEF(def_name)
%define GO4K_END_PARAMDEF
GO4K_ENV_ID		equ		1
%macro	GO4K_ENV 5
	db	%1
	db	%2
	db	%3
	db	%4
	db	%5
%endmacro
%define	ATTAC(val)		val	
%define	DECAY(val)		val	
%define	SUSTAIN(val)	val	
%define	RELEASE(val)	val	
%define	GAIN(val)		val	
struc	go4kENV_val
	.attac		resd	1
	.decay		resd	1
	.sustain	resd	1
	.release	resd	1
	.gain		resd	1
	.size
endstruc
struc	go4kENV_wrk
	.state		resd	1
	.level		resd	1
	.gm			resd	1
	.am			resd	1
	.dm			resd	1
	.sm			resd	1
	.rm			resd	1
	.size
endstruc
%define ENV_STATE_ATTAC		0
%define ENV_STATE_DECAY		1
%define ENV_STATE_SUSTAIN	2
%define ENV_STATE_RELEASE	3
%define ENV_STATE_OFF		4
GO4K_VCO_ID		equ		2
%macro	GO4K_VCO 8
	db	%1
	db	%2
%ifdef GO4K_USE_VCO_PHASE_OFFSET	
	db	%3
%endif	
%ifdef GO4K_USE_VCO_GATE	
	db	%4
%endif	
	db	%5
%ifdef GO4K_USE_VCO_SHAPE	
	db	%6
%endif	
	db	%7
	db	%8
%endmacro
%define	TRANSPOSE(val)	val	
%define	DETUNE(val)		val	
%define	PHASE(val)		val	
%define	GATES(val)		val	
%define	COLOR(val)		val	
%define	SHAPE(val)		val 
%define	FLAGS(val)		val	
%define SINE		0x01
%define TRISAW		0x02
%define PULSE		0x04
%define NOISE		0x08
%define LFO			0x10
%define GATE		0x20
%define	VCO_STEREO	0x40
struc	go4kVCO_val
	.transpose	resd	1
	.detune		resd	1
%ifdef GO4K_USE_VCO_PHASE_OFFSET	
	.phaseofs	resd	1
%endif	
%ifdef GO4K_USE_VCO_GATE	
	.gate		resd	1
%endif	
	.color		resd	1
%ifdef GO4K_USE_VCO_SHAPE	
	.shape		resd	1
%endif	
	.gain		resd	1
	.flags		resd	1	
	.size
endstruc
struc	go4kVCO_wrk
	.phase		resd	1
	.tm			resd	1
	.dm			resd	1
	.fm			resd	1
	.pm			resd	1
	.cm			resd	1
	.sm			resd	1
	.gm			resd	1
	.phase2		resd	1
	.size
endstruc
GO4K_VCF_ID		equ		3
%macro	GO4K_VCF 3
	db	%1
	db	%2
	db	%3
%endmacro
%define LOWPASS		0x1
%define HIGHPASS	0x2
%define BANDPASS	0x4
%define	BANDSTOP	0x3
%define ALLPASS		0x7
%define	PEAK		0x8
%define STEREO		0x10
%define	FREQUENCY(val)	val
%define	RESONANCE(val)	val
%define	VCFTYPE(val)	val
struc	go4kVCF_val
	.freq		resd	1
	.res		resd	1
	.type		resd	1
	.size
endstruc
struc	go4kVCF_wrk
	.low		resd	1
	.high		resd	1
	.band		resd	1
	.freq		resd	1
	.fm			resd	1
	.rm			resd	1
	.low2		resd	1
	.high2		resd	1
	.band2		resd	1
	.size
endstruc
GO4K_DST_ID		equ		4
%macro	GO4K_DST 3
	db	%1
%ifdef GO4K_USE_DST_SH
	db	%2
%ifdef GO4K_USE_DST_STEREO
	db	%3
%endif
%else
%ifdef GO4K_USE_DST_STEREO
	db	%3
%endif
%endif
%endmacro
%define	DRIVE(val)		val
%define	SNHFREQ(val)	val
%define	FLAGS(val)		val
struc	go4kDST_val
	.drive		resd	1
%ifdef GO4K_USE_DST_SH	
	.snhfreq	resd	1
%endif	
	.flags		resd	1
	.size
endstruc
struc	go4kDST_wrk
	.out		resd	1
	.snhphase	resd	1
	.dm			resd	1
	.sm			resd	1
	.out2		resd	1
	.size
endstruc
GO4K_DLL_ID		equ		5
%macro	GO4K_DLL 8
	db	%1
	db	%2
	db	%3
%ifdef GO4K_USE_DLL_DAMP	
	db	%4
%endif		
%ifdef GO4K_USE_DLL_CHORUS	
	db	%5
	db	%6
%endif
	db	%7
	db	%8
%endmacro
%define PREGAIN(val)	val
%define	DRY(val)		val
%define	FEEDBACK(val)	val
%define	DEPTH(val)		val
%define DAMP(val)		val
%define	DELAY(val)		val
%define	COUNT(val)		val
struc	go4kDLL_val
	.pregain	resd	1
	.dry		resd	1
	.feedback	resd	1
%ifdef GO4K_USE_DLL_DAMP	
	.damp		resd	1	
%endif
%ifdef GO4K_USE_DLL_CHORUS
	.freq		resd	1
	.depth
%endif
	.delay		resd	1
	.count		resd	1
	.size
endstruc
struc	go4kDLL_wrk
	.index		resd	1
	.store		resd	1
	.dcin		resd	1
	.dcout		resd	1
%ifdef GO4K_USE_DLL_CHORUS
	.phase		resd	1
%endif
	.buffer		resd	MAX_DELAY
	.size
endstruc
struc	go4kDLL_wrk2
 .pm			resd	1
 .fm			resd	1
 .im			resd	1
 .dm			resd	1
 .sm			resd	1
 .am			resd	1
 .size
endstruc
GO4K_FOP_ID	equ			6
%macro	GO4K_FOP 1
	db	%1
%endmacro
%define	OP(val)			val
%define FOP_POP			0x1
%define FOP_ADDP		0x2
%define FOP_MULP		0x3
%define FOP_PUSH		0x4
%define FOP_XCH			0x5
%define FOP_ADD			0x6
%define FOP_MUL			0x7
%define FOP_ADDP2		0x8
%define FOP_LOADNOTE	0x9
%define FOP_MULP2		0xa
struc	go4kFOP_val
	.flags		resd	1
	.size
endstruc
struc	go4kFOP_wrk
	.size
endstruc
GO4K_FST_ID		equ		7
%macro	GO4K_FST 2
	db	%1
	dw	%2
%endmacro
%define	AMOUNT(val)		val
%define	DEST(val)		val
%define	FST_SET			0x0000
%define	FST_ADD			0x4000
%define	FST_POP			0x8000
struc	go4kFST_val
	.amount		resd	1
	.op1		resd	1
	.size
endstruc
struc	go4kFST_wrk
	.size
endstruc
GO4K_PAN_ID		equ		8
%macro	GO4K_PAN 1
%ifdef GO4K_USE_PAN
	db	%1
%endif
%endmacro
%define	PANNING(val)	val
struc	go4kPAN_val
%ifdef GO4K_USE_PAN
	.panning	resd	1
%endif
	.size
endstruc
struc	go4kPAN_wrk
	.pm			resd	1
	.size
endstruc
GO4K_OUT_ID		equ		9
%macro	GO4K_OUT 2
	db	%1
%ifdef GO4K_USE_GLOBAL_DLL	
	db	%2
%endif	
%endmacro
%define	AUXSEND(val)	val
struc	go4kOUT_val
	.gain		resd	1
%ifdef GO4K_USE_GLOBAL_DLL	
	.auxsend	resd	1
%endif
	.size
endstruc
struc	go4kOUT_wrk
	.am			resd	1
	.gm			resd	1
	.size
endstruc
GO4K_ACC_ID		equ		10
%macro	GO4K_ACC 1
	db	%1
%endmacro
%define OUTPUT			0
%define	AUX				8
%define ACCTYPE(val)	val
struc	go4kACC_val
	.acctype	resd	1
	.size
endstruc
struc	go4kACC_wrk
	.size
endstruc
%ifdef GO4K_USE_FLD
GO4K_FLD_ID	equ		11
%macro	GO4K_FLD 1
	db	%1
%endmacro
%define	VALUE(val)	val
struc	go4kFLD_val
	.value		resd	1
	.size
endstruc
struc	go4kFLD_wrk
	.vm			resd	1
	.size
endstruc
%endif
%ifdef GO4K_USE_GLITCH
GO4K_GLITCH_ID		equ		12
%macro	GO4K_GLITCH 5
	db	%1
	db	%2
	db	%3
	db	%4
	db	%5
%endmacro
%define	ACTIVE(val)		val
%define	SLICEFACTOR(val)val
%define	PITCHFACTOR(val)val
%define	SLICESIZE(val)	val
struc	go4kGLITCH_val
	.active		resd	1
	.dry		resd	1
	.dsize		resd	1
	.dpitch		resd	1
	.slicesize	resd	1
	.size
endstruc
struc	go4kGLITCH_wrk
	.index		resd	1
	.store		resd	1
	.slizesize	resd	1
	.slicepitch	resd	1
	.unused		resd	1
	.buffer		resd	MAX_DELAY
	.size
endstruc
struc	go4kGLITCH_wrk2
	.am			resd	1
	.dm			resd	1
	.sm			resd	1
	.pm			resd	1
	.size
endstruc
%endif
%ifdef GO4K_USE_FSTG
GO4K_FSTG_ID	equ		13
%macro	GO4K_FSTG 2
	db	%1
	dw	%2
%endmacro
struc	go4kFSTG_val
	.amount		resd	1
	.op1		resd	1
	.size
endstruc
struc	go4kFSTG_wrk
	.size
endstruc
%endif
struc	go4k_instrument
	.release	resd	1
	.note		resd	1
	.workspace	resd	MAX_UNITS*MAX_UNIT_SLOTS
	.dlloutl	resd	1
	.dlloutr	resd	1
	.outl		resd	1
	.outr		resd	1
	.size
endstruc
struc	go4k_synth
	.instruments	resb	go4k_instrument.size * MAX_INSTRUMENTS * MAX_VOICES
	.global			resb	go4k_instrument.size * MAX_VOICES
	.size
endstruc
%ifdef USE_SECTIONS
section .g4kmuc1 data align=1
%else
section .data align=1
%endif
go4k_patterns
	db	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	db	78, 74, HLD, 74, 80, 0, 0, 0, 81, HLD, HLD, HLD, 83, HLD, HLD, HLD, 85, HLD, HLD, HLD, 81, HLD, HLD, HLD, 83, HLD, HLD, HLD, 81, HLD, HLD, HLD, 
	db	80, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 78, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 78, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 
	db	78, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 80, HLD, HLD, HLD, 81, HLD, HLD, HLD, 83, HLD, HLD, HLD, 85, HLD, HLD, HLD, 83, HLD, HLD, HLD, 88, HLD, HLD, HLD, 
	db	85, HLD, HLD, HLD, 83, HLD, HLD, HLD, 85, HLD, HLD, HLD, 81, HLD, HLD, HLD, 80, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 78, HLD, HLD, HLD, 
	db	90, HLD, HLD, HLD, 88, HLD, 87, HLD, HLD, HLD, HLD, HLD, 83, HLD, HLD, HLD, 88, HLD, 81, HLD, HLD, HLD, 80, HLD, 0, 0, 0, 0, 81, HLD, HLD, HLD, 
	db	83, HLD, HLD, HLD, 85, HLD, HLD, HLD, 88, HLD, HLD, HLD, 83, HLD, 85, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 0, 0, 
	db	54, HLD, HLD, HLD, 56, HLD, HLD, HLD, 57, HLD, HLD, HLD, 61, HLD, HLD, HLD, 59, HLD, HLD, HLD, 57, HLD, HLD, HLD, 59, HLD, HLD, HLD, 56, HLD, HLD, HLD, 
	db	54, HLD, HLD, HLD, 56, HLD, HLD, HLD, 57, HLD, HLD, HLD, 59, HLD, HLD, HLD, 61, HLD, HLD, HLD, 59, HLD, HLD, HLD, 57, HLD, HLD, HLD, 64, HLD, HLD, HLD, 
	db	54, HLD, HLD, HLD, 66, HLD, HLD, HLD, 62, HLD, HLD, HLD, 61, HLD, HLD, HLD, 59, HLD, HLD, HLD, 61, HLD, HLD, HLD, 57, HLD, HLD, HLD, 56, HLD, HLD, HLD, 
	db	78, HLD, 80, HLD, 81, HLD, 83, HLD, 85, HLD, 88, HLD, 86, HLD, 85, HLD, 81, HLD, HLD, HLD, 85, HLD, 81, HLD, 85, HLD, 85, HLD, 86, HLD, 85, HLD, 
	db	83, HLD, HLD, HLD, 90, HLD, 85, HLD, 83, HLD, 83, HLD, 81, HLD, 85, HLD, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	db	93, 92, 93, 97, 90, HLD, 95, HLD, 95, 95, 95, HLD, 95, 97, 95, 93, 97, 97, 97, HLD, 100, 98, 97, 95, 97, 85, 102, 100, 89, 90, 92, 93, 
	db	92, HLD, HLD, HLD, 102, 101, 102, HLD, 97, 96, 97, HLD, 95, 97, 95, 93, 97, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 0, 0, 0, 0, 0, 0, 0, 0, 
	db	102, HLD, 0, 0, 100, HLD, 0, 0, 99, HLD, 98, HLD, 97, HLD, 0, 0, 97, HLD, 96, HLD, 95, HLD, 93, HLD, 92, HLD, 0, 0, 90, HLD, 89, HLD, 
	db	90, HLD, 92, HLD, 93, HLD, 97, HLD, 95, HLD, 97, HLD, 100, HLD, 97, HLD, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	db	61, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 57, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 56, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 57, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 
	db	61, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 57, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 64, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 61, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 
	db	61, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 57, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 57, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 54, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 
	db	54, HLD, HLD, HLD, 56, HLD, HLD, HLD, 57, HLD, HLD, HLD, 61, HLD, HLD, HLD, 59, HLD, HLD, HLD, 56, HLD, HLD, HLD, 57, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 
	db	54, HLD, HLD, HLD, 56, HLD, HLD, HLD, 57, HLD, HLD, HLD, 61, HLD, HLD, HLD, 59, HLD, HLD, HLD, 56, HLD, HLD, HLD, 64, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 
	db	64, HLD, 61, HLD, 59, HLD, 61, HLD, 68, HLD, HLD, HLD, 64, HLD, 68, HLD, 69, HLD, 68, HLD, 66, HLD, 64, HLD, 64, HLD, 66, HLD, 61, HLD, 59, HLD, 
	db	57, HLD, 59, HLD, 61, HLD, 64, HLD, 57, HLD, 54, HLD, 54, HLD, 61, HLD, 59, HLD, 59, HLD, 57, HLD, 61, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 
	db	54, 56, 57, 61, HLD, 64, 61, 59, 57, 59, 61, 66, 64, 61, 64, HLD, 68, 69, 0, 73, 66, 71, HLD, 0, 76, 74, 73, 69, 71, 68, HLD, 0, 
	db	68, 69, 71, 73, 66, HLD, HLD, HLD, 73, 73, 73, 73, 73, HLD, HLD, HLD, 78, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 80, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 
	db	81, 80, 78, 73, 78, 80, 81, 83, 85, 78, 88, 86, 85, 81, 85, 81, 83, HLD, 80, HLD, 76, HLD, 80, HLD, 81, 80, 78, 76, 78, HLD, HLD, HLD, 
	db	81, 80, 78, 76, 78, 73, 76, 74, 73, 69, 73, HLD, 71, HLD, HLD, HLD, 73, 71, 69, 64, 71, HLD, HLD, HLD, 71, 69, 68, 64, 66, HLD, HLD, HLD, 
	db	90, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 92, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 
	db	93, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 97, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 
	db	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 90, HLD, 
	db	0, 0, 90, HLD, 0, 0, 90, HLD, 0, 0, 90, HLD, 0, 0, 90, HLD, 0, 0, 90, HLD, 0, 0, 90, HLD, 0, 0, 90, HLD, 92, HLD, 93, HLD, 
	db	95, HLD, 97, HLD, 90, HLD, 93, HLD, 97, HLD, 100, HLD, 97, HLD, 97, HLD, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	db	0, 0, 0, 36, 0, 0, 0, 36, 0, 0, 0, 36, 0, 0, 0, 36, 0, 0, 0, 36, 0, 0, 0, 36, 0, 36, HLD, 0, 36, 0, 0, 0, 
	db	36, HLD, HLD, 0, 0, 0, 0, 0, 36, HLD, HLD, 0, 0, 0, 0, 0, 36, HLD, HLD, 0, 0, 0, 0, 0, 36, 0, 0, 36, 0, 36, HLD, HLD, 
	db	36, HLD, HLD, 0, 0, 0, 0, 0, 36, HLD, HLD, 0, 0, 0, 0, 0, 36, HLD, HLD, 0, 36, HLD, HLD, 0, 36, 0, 0, 36, 0, 36, HLD, HLD, 
	db	36, HLD, HLD, 0, 0, 0, 0, 0, 36, HLD, HLD, 0, 36, HLD, HLD, 0, 36, HLD, HLD, 0, 36, HLD, HLD, 0, 36, 0, 0, 36, 0, 36, HLD, HLD, 
	db	36, HLD, HLD, 0, 36, HLD, HLD, 0, 36, HLD, HLD, 0, 36, HLD, HLD, 0, 36, HLD, HLD, 0, 36, HLD, HLD, 0, 36, 0, 0, 36, 0, 36, HLD, HLD, 
	db	78, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 81, HLD, HLD, HLD, 83, HLD, 85, HLD, HLD, HLD, HLD, HLD, 83, HLD, 83, HLD, HLD, HLD, HLD, HLD, 81, HLD, 85, HLD, 
	db	HLD, HLD, HLD, HLD, 83, HLD, 83, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	db	78, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 90, HLD, HLD, HLD, 85, HLD, 83, HLD, HLD, HLD, HLD, HLD, 83, HLD, 83, HLD, HLD, HLD, HLD, HLD, 83, HLD, 83, HLD, 
	db	HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 81, HLD, 78, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 
	db	42, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 40, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 
	db	39, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 38, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 
	db	42, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 42, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 40, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 40, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 
	db	39, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 39, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 38, HLD, HLD, HLD, 38, HLD, HLD, HLD, 38, HLD, HLD, HLD, 38, HLD, HLD, HLD, 
	db	66, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 68, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 
	db	69, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 73, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 
	db	69, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 76, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 73, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 
	db	66, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 76, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 
	db	73, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 69, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 68, HLD, HLD, HLD, HLD, HLD, HLD, HLD, 
go4k_patterns_end
%ifdef USE_SECTIONS
section .g4kmuc2 data align=1
%else
section .data
%endif
go4k_pattern_lists
Instrument0List		db	1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0, 0, 10, 11, 12, 13, 14, 15, 
Instrument1List		db	16, 17, 16, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 0, 29, 30, 31, 
Instrument2List		db	32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 
Instrument3List		db	33, 34, 33, 33, 35, 36, 36, 36, 36, 36, 36, 36, 33, 33, 36, 36, 36, 36, 
Instrument4List		db	0, 0, 37, 38, 39, 40, 0, 0, 0, 0, 0, 0, 37, 38, 0, 0, 0, 0, 
Instrument5List		db	41, 42, 41, 42, 41, 42, 41, 42, 41, 42, 41, 42, 41, 42, 43, 44, 41, 42, 
Instrument6List		db	45, 46, 45, 47, 48, 49, 45, 46, 45, 47, 48, 49, 45, 46, 45, 47, 48, 49, 
go4k_pattern_lists_end
%ifdef USE_SECTIONS
section .g4kmuc3 data align=1
%else
section .data
%endif
go4k_synth_instructions
GO4K_BEGIN_CMDDEF(Instrument0)
	db GO4K_ENV_ID
	db GO4K_VCO_ID
	db GO4K_VCO_ID
	db GO4K_FOP_ID
	db GO4K_FOP_ID
	db GO4K_PAN_ID
	db GO4K_OUT_ID
GO4K_END_CMDDEF
GO4K_BEGIN_CMDDEF(Instrument1)
	db GO4K_ENV_ID
	db GO4K_VCO_ID
	db GO4K_FST_ID
	db GO4K_FOP_ID
	db GO4K_VCO_ID
	db GO4K_FOP_ID
	db GO4K_VCF_ID
	db GO4K_PAN_ID
	db GO4K_OUT_ID
GO4K_END_CMDDEF
GO4K_BEGIN_CMDDEF(Instrument2)
	db GO4K_ENV_ID
	db GO4K_VCO_ID
	db GO4K_FOP_ID
	db GO4K_VCF_ID
	db GO4K_PAN_ID
	db GO4K_OUT_ID
GO4K_END_CMDDEF
GO4K_BEGIN_CMDDEF(Instrument3)
	db GO4K_ENV_ID
	db GO4K_FST_ID
	db GO4K_VCO_ID
	db GO4K_FOP_ID
	db GO4K_VCF_ID
	db GO4K_PAN_ID
	db GO4K_OUT_ID
GO4K_END_CMDDEF
GO4K_BEGIN_CMDDEF(Instrument4)
	db GO4K_ENV_ID
	db GO4K_VCO_ID
	db GO4K_FOP_ID
	db GO4K_DLL_ID
	db GO4K_PAN_ID
	db GO4K_OUT_ID
GO4K_END_CMDDEF
GO4K_BEGIN_CMDDEF(Instrument5)
	db GO4K_ENV_ID
	db GO4K_FST_ID
	db GO4K_ENV_ID
	db GO4K_VCO_ID
	db GO4K_FOP_ID
	db GO4K_VCF_ID
	db GO4K_DLL_ID
	db GO4K_VCF_ID
	db GO4K_FOP_ID
	db GO4K_PAN_ID
	db GO4K_OUT_ID
GO4K_END_CMDDEF
GO4K_BEGIN_CMDDEF(Instrument6)
	db GO4K_ENV_ID
	db GO4K_FST_ID
	db GO4K_ENV_ID
	db GO4K_VCO_ID
	db GO4K_FOP_ID
	db GO4K_VCF_ID
	db GO4K_DLL_ID
	db GO4K_VCF_ID
	db GO4K_FOP_ID
	db GO4K_PAN_ID
	db GO4K_OUT_ID
GO4K_END_CMDDEF
GO4K_BEGIN_CMDDEF(Global)
	db GO4K_ACC_ID
	db GO4K_DLL_ID
	db GO4K_FOP_ID
	db GO4K_DLL_ID
	db GO4K_FOP_ID
	db GO4K_ACC_ID
	db GO4K_FOP_ID
	db GO4K_OUT_ID
GO4K_END_CMDDEF
go4k_synth_instructions_end
%ifdef USE_SECTIONS
section .g4kmuc4 data align=1
%else
section .data
%endif
go4k_synth_parameter_values
GO4K_BEGIN_PARAMDEF(Instrument0)
	GO4K_ENV	ATTAC(0),DECAY(74),SUSTAIN(0),RELEASE(74),GAIN(128)
	GO4K_VCO	TRANSPOSE(64),DETUNE(64),PHASE(64),GATES(85),COLOR(128),SHAPE(96),GAIN(128),FLAGS(SINE)
	GO4K_VCO	TRANSPOSE(64),DETUNE(64),PHASE(64),GATES(85),COLOR(128),SHAPE(96),GAIN(128),FLAGS(SINE)
	GO4K_FOP	OP(FOP_MULP)
	GO4K_FOP	OP(FOP_MULP)
	GO4K_PAN	PANNING(64)
	GO4K_OUT	GAIN(64), AUXSEND(93)
GO4K_END_PARAMDEF
GO4K_BEGIN_PARAMDEF(Instrument1)
	GO4K_ENV	ATTAC(0),DECAY(96),SUSTAIN(0),RELEASE(64),GAIN(128)
	GO4K_VCO	TRANSPOSE(64),DETUNE(73),PHASE(0),GATES(85),COLOR(128),SHAPE(64),GAIN(128),FLAGS(SINE)
	GO4K_FST	AMOUNT(96),DEST(4*MAX_UNIT_SLOTS+4+FST_SET)
	GO4K_FOP	OP(FOP_POP)
	GO4K_VCO	TRANSPOSE(64),DETUNE(64),PHASE(64),GATES(85),COLOR(128),SHAPE(64),GAIN(128),FLAGS(SINE)
	GO4K_FOP	OP(FOP_MULP)
	GO4K_VCF	FREQUENCY(48),RESONANCE(64),VCFTYPE(LOWPASS)
	GO4K_PAN	PANNING(64)
	GO4K_OUT	GAIN(96), AUXSEND(4)
GO4K_END_PARAMDEF
GO4K_BEGIN_PARAMDEF(Instrument2)
	GO4K_ENV	ATTAC(0),DECAY(64),SUSTAIN(0),RELEASE(0),GAIN(128)
	GO4K_VCO	TRANSPOSE(64),DETUNE(64),PHASE(64),GATES(85),COLOR(64),SHAPE(64),GAIN(128),FLAGS(NOISE)
	GO4K_FOP	OP(FOP_MULP)
	GO4K_VCF	FREQUENCY(128),RESONANCE(128),VCFTYPE(HIGHPASS)
	GO4K_PAN	PANNING(64)
	GO4K_OUT	GAIN(64), AUXSEND(0)
GO4K_END_PARAMDEF
GO4K_BEGIN_PARAMDEF(Instrument3)
	GO4K_ENV	ATTAC(0),DECAY(81),SUSTAIN(0),RELEASE(0),GAIN(61)
	GO4K_FST	AMOUNT(128),DEST(0*MAX_UNIT_SLOTS+2+FST_SET)
	GO4K_VCO	TRANSPOSE(64),DETUNE(64),PHASE(64),GATES(85),COLOR(64),SHAPE(94),GAIN(128),FLAGS(NOISE)
	GO4K_FOP	OP(FOP_MULP)
	GO4K_VCF	FREQUENCY(22),RESONANCE(128),VCFTYPE(LOWPASS)
	GO4K_PAN	PANNING(64)
	GO4K_OUT	GAIN(64), AUXSEND(0)
GO4K_END_PARAMDEF
GO4K_BEGIN_PARAMDEF(Instrument4)
	GO4K_ENV	ATTAC(64),DECAY(64),SUSTAIN(64),RELEASE(64),GAIN(128)
	GO4K_VCO	TRANSPOSE(64),DETUNE(64),PHASE(0),GATES(0),COLOR(64),SHAPE(64),GAIN(128),FLAGS(SINE)
	GO4K_FOP	OP(FOP_MULP)
	GO4K_DLL	PREGAIN(64),DRY(128),FEEDBACK(64),DAMP(64),FREQUENCY(0),DEPTH(0),DELAY(17),COUNT(1)
	GO4K_PAN	PANNING(64)
	GO4K_OUT	GAIN(64), AUXSEND(0)
GO4K_END_PARAMDEF
GO4K_BEGIN_PARAMDEF(Instrument5)
	GO4K_ENV	ATTAC(0),DECAY(48),SUSTAIN(128),RELEASE(64),GAIN(128)
	GO4K_FST	AMOUNT(116),DEST(0*MAX_UNIT_SLOTS+2+FST_SET)
	GO4K_ENV	ATTAC(0),DECAY(56),SUSTAIN(0),RELEASE(0),GAIN(128)
	GO4K_VCO	TRANSPOSE(64),DETUNE(64),PHASE(0),GATES(85),COLOR(64),SHAPE(64),GAIN(128),FLAGS(NOISE)
	GO4K_FOP	OP(FOP_MULP)
	GO4K_VCF	FREQUENCY(48),RESONANCE(128),VCFTYPE(LOWPASS)
	GO4K_DLL	PREGAIN(128),DRY(128),FEEDBACK(127),DAMP(8),FREQUENCY(0),DEPTH(0),DELAY(0),COUNT(1)
	GO4K_VCF	FREQUENCY(48),RESONANCE(128),VCFTYPE(LOWPASS)
	GO4K_FOP	OP(FOP_MULP)
	GO4K_PAN	PANNING(64)
	GO4K_OUT	GAIN(64), AUXSEND(16)
GO4K_END_PARAMDEF
GO4K_BEGIN_PARAMDEF(Instrument6)
	GO4K_ENV	ATTAC(0),DECAY(48),SUSTAIN(128),RELEASE(64),GAIN(128)
	GO4K_FST	AMOUNT(116),DEST(0*MAX_UNIT_SLOTS+2+FST_SET)
	GO4K_ENV	ATTAC(0),DECAY(56),SUSTAIN(0),RELEASE(0),GAIN(128)
	GO4K_VCO	TRANSPOSE(64),DETUNE(64),PHASE(0),GATES(85),COLOR(64),SHAPE(64),GAIN(128),FLAGS(NOISE)
	GO4K_FOP	OP(FOP_MULP)
	GO4K_VCF	FREQUENCY(48),RESONANCE(128),VCFTYPE(LOWPASS)
	GO4K_DLL	PREGAIN(128),DRY(128),FEEDBACK(127),DAMP(8),FREQUENCY(0),DEPTH(0),DELAY(0),COUNT(1)
	GO4K_VCF	FREQUENCY(48),RESONANCE(128),VCFTYPE(LOWPASS)
	GO4K_FOP	OP(FOP_MULP)
	GO4K_PAN	PANNING(64)
	GO4K_OUT	GAIN(64), AUXSEND(16)
GO4K_END_PARAMDEF
GO4K_BEGIN_PARAMDEF(Global)
	GO4K_ACC	ACCTYPE(AUX)
	GO4K_DLL	PREGAIN(40),DRY(128),FEEDBACK(125),DAMP(64),FREQUENCY(0),DEPTH(0),DELAY(1),COUNT(8)
	GO4K_FOP	OP(FOP_XCH)
	GO4K_DLL	PREGAIN(40),DRY(128),FEEDBACK(125),DAMP(64),FREQUENCY(0),DEPTH(0),DELAY(9),COUNT(8)
	GO4K_FOP	OP(FOP_XCH)
	GO4K_ACC	ACCTYPE(OUTPUT)
	GO4K_FOP	OP(FOP_ADDP2)
	GO4K_OUT	GAIN(64), AUXSEND(0)
GO4K_END_PARAMDEF
go4k_synth_parameter_values_end
%ifdef USE_SECTIONS
section .g4kmuc5 data align=1
%else
section .data
%endif
%ifdef GO4K_USE_DLL
global _go4k_delay_times
_go4k_delay_times
	dw 0
	dw 1116
	dw 1188
	dw 1276
	dw 1356
	dw 1422
	dw 1492
	dw 1556
	dw 1618
	dw 1140
	dw 1212
	dw 1300
	dw 1380
	dw 1446
	dw 1516
	dw 1580
	dw 1642
	dw 18900
%endif
section .data
	global _4klang_current_tick
_4klang_current_tick: dd 0

section .text
	global _4klang_render
