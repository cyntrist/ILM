Shader "Custom/01MarcaAgua"
{
    Properties
    {
        [IntRange] _factor("_factor", Range(1, 10)) = 7
    }

    SubShader
    {
        Cull Off ZWrite Off ZTest Always // No culling or depth
        Pass 
        {
        Name "WaterMark"
            HLSLPROGRAM
            #pragma vertex Vert // Funcion Vert en Blit . hlsl
            #pragma fragment frag

            #include "Packages/com.unity.render-pipelines.universal/ShaderLibrary/Core.hlsl"
            #include "Packages/com.unity.render-pipelines.core/Runtime/Utilities/Blit.hlsl"

            // TEXTURE2D_X ( _BlitTexture );
            SAMPLER(sampler_BlitTexture);

            CBUFFER_START(UnityPerMaterial)
                int _factor;
            CBUFFER_END

            half4 frag(Varyings input) : SV_Target
            {
                half4 color =  SAMPLE_TEXTURE2D_X(_BlitTexture, sampler_BlitTexture, input.texcoord);
                int4 colorInt = color * _factor; 
                color = colorInt / _factor;
                return color;
            }
            ENDHLSL
        }
    }
}
