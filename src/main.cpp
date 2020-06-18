/*
	MIT License

	Copyright (c) 2020 Verok & Ben80

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/

// VS 6.0
// > rc main.rc
// > cl main.cpp main.res /nologo /MD /W0 /O1 /GF /link /out:h3_fix.asi /debug:none /dll /merge:.text=.asi /merge:.rdata=.asi /section:.asi,re

// VS 2008
// > rc main.rc
// > cl main.cpp main.res /nologo /MD /GS- /GL /O1 /Os /GF /link /out:h3_fix.asi /debug:none /manifest:no /merge:.text=.asi /merge:.rdata=.asi /section:.asi,re

// VS 2019
// > rc main.rc
// > cl main.cpp main.res /nologo /MD /GS- /GL /O1 /Os /GF /link /out:h3_fix.asi /debug:none /emitpogophaseinfo /merge:.text=.rdata /merge:.rdata=.asi /section:.asi,re

#define WIN32_LEAN_AND_MEAN

#include "windows.h"
#include "hooker.h"
#include "H3Structures.h"
#include "H3Numerations.h"

#pragma comment(lib, "kernel32.lib")

#pragma pack(1)
const struct AddressSpace {
	DWORD pattern_check[2];
	DWORD armorer_fix[3];
	DWORD creatures_luck[2];
	struct {
		DWORD hook;
		BYTE type;
	} lighthouse_bonus;
	struct {
		DWORD hook;
		DWORD cast;
		DWORD skip;
		BYTE type;
	} ai_water_walk_fly;
	DWORD tavern_rumors;
} addressSpace[] = {
// === RUS ======================================================================================================================================
#pragma region RUS
	// Heroes III Erathia - v1.0 Buka
	0x004D4A5F, 0x0059308B,
	0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000,
	0x00000000, 0,
	0x00000000, 0x00000000, 0x00000000, 1,
	0x004B0570,

	// Heroes III Armageddon - v2.1 Buka
	0x004F2533, 0x005F9649,
	0x0041D5B3, 0x0041D6F1, 0x004640FD,
	0x00440545, 0x0043E686,
	0x004DFE30, 0,
	0x0042EDC8, 0x0042EDEB, 0x0042F10B, 0,
	0x004C8550,

	// Heroes III Armageddon - v2.2 Buka
	0x004F2863, 0x005F9609,
	0x0041D553, 0x0041D691, 0x00463D9D,
	0x00440045, 0x0043E186,
	0x004E02F0, 0,
	0x0042ED98, 0x0042EDBB, 0x0042F0DB, 0,
	0x004C87E0,

	// Heroes III Shadow - v3.1 Buka
	0x004F7EB3, 0x00602379,
	0x0041E2D3, 0x0041E40F, 0x00465EF3,
	0x00441DA4, 0x0043FEC2,
	0x004E4A20, 0,
	0x004300DE, 0x00430101, 0x00430410, 0,
	0x004CCD40,

	// Heroes III Complete - v4.0 Buka
	0x004F7EB3, 0x006021A9,
	0x0041E456, 0x0041E595, 0x0046592C,
	0x00441626, 0x0043F7B2,
	0x004E4ED0, 0,
	0x004301E6, 0x00430209, 0x00430519, 0,
	0x004CCFE0,

	// ----------------------------------------------------------------------------------------------------------------------------------------------

	// Heroes Chronicles Warlords & Underworld & Elements & Dragons - v1.0
	0x004EBA34, 0x005AF329,
	0x0041D5F3, 0x0041D731, 0x00461206,
	0x0043E0F6, 0x0043FFB5,
	0x004D9107, 0,
	0x0042ED78, 0x0042ED9B, 0x0042F0BB, 0,
	0x004C1150,

	// Heroes Chronicles Beastmaster & Sword - v1.0
	0x004EB494, 0x005AF2D9,
	0x0041D6A3, 0x0041D7E1, 0x00461126,
	0x0043FD05, 0x0043DE46,
	0x004D8EC7, 0,
	0x0042EE68, 0x0042EE8B, 0x0042F1AB, 0,
	0x004C1410,
#pragma endregion

// === ENG ======================================================================================================================================
#pragma region ENG
	// Heroes III Erathia - v1.0
	0x004D3363, 0x0058E558,
	0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000,
	0x00000000, 0,
	0x0042E079, 0x0042E09C, 0x0042E39B, 0,
	0x004AF690,

	// Heroes III Erathia - v1.1
	0x0041E573, 0x004210B8,
	0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000,
	0x00000000, 0,
	0x0044DA49, 0x0044DA6C, 0x0044DD6B, 0,
	0x004C11D0,

	// Heroes III Erathia - v1.2
	0x0041E523, 0x00421078,
	0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000,
	0x00000000, 0,
	0x0044D8E9, 0x0044D90C, 0x0044DC0B, 0,
	0x004C1410,

	// Heroes III Erathia - v1.3
	0x004F58F3, 0x005D9679,
	0x0041E003, 0x0041E13F, 0x00465203,
	0x00000000, 0x00000000,
	0x004E27A0, 0,
	0x0042FE4E, 0x0042FE71, 0x00430180, 0,
	0x004CAA90,

	// Heroes III Erathia - v1.4
	0x004F5583, 0x005D8F69,
	0x0041E343, 0x0041E47F, 0x004653D3,
	0x00000000, 0x00000000,
	0x004E25F0, 0,
	0x0043017E, 0x004301A1, 0x004304B0, 0,
	0x004CA6C0,

	// ----------------------------------------------------------------------------------------------------------------------------------------------

	// Heroes III Armageddon - v2.0
	0x004EB283, 0x005EEFD8,
	0x0041DDE3, 0x0041DF1F, 0x00460C59,
	0x00440850, 0x0043E992,
	0x004D91D0, 1,
	0x0042F8F9, 0x0042F91C, 0x0042FC1B, 0,
	0x004C3290,

	// Heroes III Armageddon - v2.1
	0x004F5C43, 0x00600299,
	0x0041E343, 0x0041E47F, 0x00465A23,
	0x004416D4, 0x0043F7F2,
	0x004E2D90, 0,
	0x0043015E, 0x00430181, 0x00430490, 0,
	0x004CAF80,

	// Heroes III Armageddon - v2.2
	0x004F5963, 0x005FFBF9,
	0x0041E033, 0x0041E16F, 0x00465A53,
	0x00441904, 0x0043FA22,
	0x004E2940, 0,
	0x0042FE6E, 0x0042FE91, 0x004301A0, 0,
	0x004CB020,

	// ----------------------------------------------------------------------------------------------------------------------------------------------

	// Heroes III Shadow - v3.0
	0x004F7D73, 0x006027E9,
	0x0041E4B3, 0x0041E5EF, 0x00465D63,
	0x00441A64, 0x0043FB82,
	0x004E4930, 0,
	0x004301CE, 0x004301F1, 0x00430500, 0,
	0x004CCC30,

	// Heroes III Shadow - v3.1
	0x004F85B3, 0x006027E9,
	0x0041E203, 0x0041E33F, 0x00465B23,
	0x004414A4, 0x0043F5C2,
	0x004E5130, 0,
	0x0043001E, 0x00430041, 0x00430350, 0,
	0x00000000,

	// Heroes III Shadow - v3.2
	0x004F8193, 0x00602149,
	0x0041E3A3, 0x0041E4DF, 0x00465943,
	0x00441524, 0x0043F642,
	0x004E4D40, 0,
	0x0043020E, 0x00430231, 0x00430540, 0,
	0x004CCC40,

	// ----------------------------------------------------------------------------------------------------------------------------------------------

	// Heroes III Complete - v4.0
	0x004F7B03, 0x00601B89,
	0x0041E223, 0x0041E35F, 0x00465D63,
	0x00441804, 0x0043F922,
	0x004E4AD0, 0,
	0x0043020E, 0x00430231, 0x00430540, 0,
	0x004CCF80,

	// ==============================================================================================================================================

	// Heroes Chronicles Warlords & Underworld - v1.0
	0x004F0033, 0x005B5129,
	0x0041E1A3, 0x0041E2DF, 0x0046364C,
	0x00441D34, 0x0043FE52,
	0x004DCB70, 1,
	0x0042FF0E, 0x0042FF31, 0x00430240, 0,
	0x004C5160,

	// Heroes Chronicles Elements & Dragons - v1.0
	0x004EFE04, 0x005B5469,
	0x0041E1C3, 0x0041E2FF, 0x004632CC,
	0x00441744, 0x0043F862,
	0x004DCB30, 1,
	0x0042FFEE, 0x00430011, 0x00430320, 0,
	0x004C4B90,

	// Heroes Chronicles WorldTree - v1.0
	0x004EFA84, 0x005B51B9,
	0x0041E163, 0x0041E29F, 0x0046326C,
	0x004418F4, 0x0043FA12,
	0x004DC5E0, 1,
	0x0042FEBE, 0x0042FEE1, 0x004301F0, 0,
	0x004C4AF0,

	// Heroes Chronicles FieryMoon - v1.0
	0x004EF824, 0x005B5249,
	0x0041E183, 0x0041E2BF, 0x00462CDC,
	0x00441424, 0x0043F542,
	0x004DC760, 1,
	0x0042FEDE, 0x0042FF01, 0x00430210, 0,
	0x004C4810,

	// Heroes Chronicles Beastmaster & Sword - v1.0
	0x004EF874, 0x005B4C09,
	0x0041E213, 0x0041E34F, 0x00462E5C,
	0x00441514, 0x0043F632,
	0x004DC670, 1,
	0x0042FF46, 0x0042FF69, 0x00430279, 0,
	0x004C4520,
#pragma endregion

// === USA ======================================================================================================================================
#pragma region USA
	// Heroes Chronicles Beastmaster & Sword - v1.0
	0x004EF914, 0x005B51B9,
	0x0041E433, 0x0041E56F, 0x0046345C,
	0x004419E4, 0x0043FB02,
	0x004DC850, 1,
	0x0043018E, 0x004301B1, 0x004304C0, 0,
	0x004C4B40,
#pragma endregion

// === GER ======================================================================================================================================
#pragma region GER
	// Heroes III Erathia - v1.2
	0x004D5253, 0x00591B29,
	0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000,
	0x00000000, 0,
	0x0042E5FB, 0x0042E61E, 0x0042E94D, 0,
	0x004B1500,

	// ==============================================================================================================================================

	// Heroes Chronicles Dragons - GOG - v1.0
	0x004EFA04, 0x005B51C9,
	0x0041E0F3, 0x0041E22F, 0x00462C0C,
	0x00441354, 0x0043F472,
	0x004DC940, 1,
	0x0042FE4E, 0x0042FE71, 0x00430180, 0,
	0x004C43C0,
#pragma endregion

// === FRA ======================================================================================================================================
#pragma region FRA
	// Heroes III Armageddon - v2.1
	0x004F61C3, 0x006003D9,
	0x0041E143, 0x0041E27F, 0x00465CB3,
	0x00441914, 0x0043FA32,
	0x004E3050, 0,
	0x0042FF5E, 0x0042FF81, 0x00430290, 0,
	0x004CB170,

	// Heroes III Shadow - v3.1
	0x004F8163, 0x006028F9,
	0x0041E413, 0x0041E54F, 0x004661B3,
	0x00441CF4, 0x0043FE12,
	0x004E4A20, 0,
	0x0043022E, 0x00430251, 0x00430560, 0,
	0x004CD040,
#pragma endregion

// === POL ======================================================================================================================================
#pragma region POL
	// Heroes III Armageddon - v2.1
	0x004F5723, 0x005FED57,
	0x0041E383, 0x0041E4BF, 0x00465813,
	0x004414A4, 0x0043F5C2,
	0x004E2890, 0,
	0x004301BE, 0x004301E1, 0x004304F0, 0,
	0x004CA910,

	// Heroes III Shadow - v3.1
	0x004F7AF3, 0x00600ED7,
	0x0041E233, 0x0041E36F, 0x00465AE3,
	0x00441574, 0x0043F692,
	0x004E44D0, 0,
	0x00430026, 0x00430049, 0x00430359, 0,
	0x004CCA10,

	// Heroes III Shadow - v3.2
	0x004F78D3, 0x00602179,
	0x0041E353, 0x0041E48F, 0x00465973,
	0x004414E4, 0x0043F602,
	0x004E4480, 0,
	0x00430136, 0x00430159, 0x00430469, 0,
	0x004CC630,

	// Heroes III Shadow - v3.2 / Armageddon - v2.2
	0x004F5993, 0x005FE337,
	0x0041E1A3, 0x0041E2DF, 0x00465903,
	0x00441764, 0x0043F883,
	0x004E2B20, 0,
	0x0042FF86, 0x0042FFA9, 0x004302B9, 0,
	0x004CAB10
#pragma endregion
};
#pragma pack()

const AddressSpace* hookSpace;

#pragma region The Castles Lighthouse building bonus
DWORD __fastcall castleOwnerCheck(H3Town* town, H3Hero* hero)
{
	return hookSpace->lighthouse_bonus.hook + (hero->owner_id == town->owner_id ? 6 : 44);
}

VOID __declspec(naked) hook_castleOwnerCheck_v0()
{
	__asm
	{
		push ecx
		mov edx, [ebp - 0x4]
		call castleOwnerCheck
		pop ecx

		mov edx, eax
		mov eax, [ecx + 0x150]
		jmp edx
	}
}

VOID __declspec(naked) hook_castleOwnerCheck_v1()
{
	__asm
	{
		push edx
		mov ecx, [ebp - 0x4]
		xchg ecx, edx
		call castleOwnerCheck
		pop edx

		mov ecx, eax
		mov eax, [edx + 0x150]
		jmp ecx
	}
}
#pragma endregion

#pragma region Prevents AI from casting Fly if they dont have it.
DWORD __fastcall ai_water_walk_fly(H3Hero* hero, BOOL hasWingth, DWORD* res)
{
	if (!hasWingth && // no angel wings
		hero->learned_spell[SPL_FLY] == 0 && hero->available_spell[SPL_FLY] == 0 && // this AI hero does not have the means to cast fly (id = 6)
		(hero->learned_spell[SPL_WATER_WALK] != 0 || hero->available_spell[SPL_WATER_WALK] != 0)) // this AI hero has access to waterwalk (id = 7)
	{
		// waterwalk is not cast ~ waterwalk field is *(&hero + 0x116) (see 0x4E6040 Cast_waterwalk function)
		// try to cast waterwalk instead (code checks for Boots of Levitation first...)
		// skip procedure
		*res = hero->waterwalk_power == -1 ? hookSpace->ai_water_walk_fly.cast : hookSpace->ai_water_walk_fly.skip;
		return TRUE;
	}

	*res = hookSpace->ai_water_walk_fly.hook;
	return FALSE;
}

VOID __declspec(naked) hook_ai_water_walk_fly_v0()
{
	__asm
	{
		push eax
		push ecx

		push esp
		mov edx, eax
		mov ecx, esi
		call ai_water_walk_fly

		pop edx
		pop ecx

		test eax, eax
		jnz lbl_ret

		add edx, 7
		push ecx
		push 0x6
		mov ecx, [ebp-0x10]
		push ecx

		lbl_ret:
		jmp edx
	}
}

VOID __declspec(naked) hook_ai_water_walk_fly_v1()
{
	__asm {
		push eax
		push ecx

		push esp
		mov edx, eax
		mov ecx, esi
		call ai_water_walk_fly

		pop edx
		pop ecx

		test eax, eax
		mov eax, edx
		jnz lbl_ret

		add eax, 8
		push ecx
		push 6
		push ebx
		lea edx, [esp-0x1C]

		lbl_ret:
		jmp eax
	}
}
#pragma endregion

VOID PatchSpace(HOOKER hooker)
{
	// Armorer fix
	if (hookSpace->armorer_fix[0])
		for (DWORD i = 0; i < sizeof(hookSpace->armorer_fix) / sizeof(DWORD); ++i)
			PatchByte(hooker, hookSpace->armorer_fix[i] + 1, 0x4D); // fdivr -> fmul

	// Neutral creatures luck
	if (hookSpace->creatures_luck[0])
		for (DWORD i = 0; i < sizeof(hookSpace->creatures_luck) / sizeof(DWORD); ++i)
			PatchNop(hooker, hookSpace->creatures_luck[i], 6);

	// Castle's Lighthouse building bonus
	if (hookSpace->lighthouse_bonus.hook)
		PatchHook(hooker, hookSpace->lighthouse_bonus.hook, !hookSpace->lighthouse_bonus.type ? hook_castleOwnerCheck_v0 : hook_castleOwnerCheck_v1);

	// Prevents AI from casting Fly if they don't have it.
	if (hookSpace->ai_water_walk_fly.hook)
		PatchHook(hooker, hookSpace->ai_water_walk_fly.hook, !hookSpace->ai_water_walk_fly.type ? hook_ai_water_walk_fly_v0 : hook_ai_water_walk_fly_v1);

	// Tavern rumors bug fix
	if (hookSpace->tavern_rumors)
	{
		DWORD arrList;
		if (ReadDWord(hooker, hookSpace->tavern_rumors + 3, &arrList))
			PatchDWord(hooker, hookSpace->tavern_rumors + 3, arrList - 4);
	}
}

extern "C" VOID __stdcall PatchMain(HOOKER hooker)
{
	hookSpace = addressSpace;
	DWORD count = sizeof(addressSpace) / sizeof(AddressSpace);
	do
	{
		DWORD check;
		if ((ReadDWord(hooker, hookSpace->pattern_check[0] + 1, &check) && check == (WS_VISIBLE | WS_POPUP)) &&
			(ReadDWord(hooker, hookSpace->pattern_check[1] + 1, &check) && check == (WS_VISIBLE | WS_POPUP)))
		{
			PatchSpace(hooker);
			break;
		}

		++hookSpace;
	} while (--count);
}
