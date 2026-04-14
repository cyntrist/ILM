Shader "Custom/03Glitch"
{
    Properties
    {
        // [MainColor] _BaseColor("Base Color", Color) = (1, 1, 1, 1)
        // [MainTexture] _BaseMap("Base Map", 2D) = "white" {}
        [IntRange] _MaxDesplX("Maximo glitch vertical (pixeles)", Range(0, 100)) = 10
    }

    SubShader
    {
        Cull Off ZWrite Off ZTest Always // No culling or depth
        Pass 
        {
        Name " Negative "
        HLSLPROGRAM
            #include "Packages/com.unity.render-pipelines.universal/ShaderLibrary/Core.hlsl"
            #include "Packages/com.unity.render-pipelines.core/Runtime/Utilities/Blit.hlsl"
        
        #pragma vertex Vert // Funcion Vert en Blit . hlsl
        #pragma fragment frag
        // TEXTURE2D_X ( _BlitTexture );
        SAMPLER ( sampler_BlitTexture );

        half4 frag ( Varyings input ) : SV_Target
        {
        return 1 - SAMPLE_TEXTURE2D_X(_BlitTexture, sampler_BlitTexture, input.texcoord);
        }

        ENDHLSL
        }
    }
}