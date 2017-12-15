/*
 * Copyright (c) 2012, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */


function getLibs(prog)
{
    var lib;
    var name = "lib/cmem";
    var suffix;

    //
    // XDCtools 3.10 has new findSuffix() function. Must pass in suffix array
    // because dsplink libraries are built with makefile instead of XDCtools.
    //
    if ("findSuffix" in prog.build.target) {
        var suffixList = ["470MV", "470uC", "bnc"];
        suffix = prog.build.target.findSuffix(suffixList);
    }
    else {
        // no findSuffix() support, do things the old way ...

        suffix = prog.build.target.suffix;

        /*
         * "470MV" covers glibc (currently MV & CodeSourcery GCC)
         * "470uC" covers uClibc
         */
        if (!suffix.match(/^470MV$|^470uC$|^bnc$/)) {
            suffix = null;
        }
    }

    if (suffix == null) {
        return ("");
    }

    /* return the library name: name.a<arch> */
    lib = name + (this.CMEM.debug ? "d" : "") + ".a" + suffix;

    return (lib);
}
/*
 *  @(#) ti.sdo.linuxutils.cmem; 2, 2, 0,1; 5-30-2012 11:50:08; /db/atree/library/trees/linuxutils/linuxutils-l01/src/ xlibrary

 */
