Shader "Custom/02ToonShader"
{   
    Properties
    {
        _factor("_factor", Range(1, 10)) = 7
    }

    SubShader
    {
        HLSLINCLUDE
        #include "Packages/com.unity.render-pipelines.universal/ShaderLibrary/Core.hlsl"
        #include "Packages/com.unity.render-pipelines.core/Runtime/Utilities/Blit.hlsl"
        ENDHLSL

        Tags { "RenderType"="Opaque" }
        LOD 100
        ZWrite Off Cull Off
        Pass
        {
            Name "02ToonShader"

            HLSLPROGRAM
            
            #pragma vertex Vert
            #pragma fragment Frag

            CBUFFER_START(UnityPerMaterial)
                int _factor;
            CBUFFER_END

            float4 Frag (Varyings input) : SV_Target
            {
                float4 color = SAMPLE_TEXTURE2D(_BlitTexture, sampler_LinearClamp, input.texcoord).rgba;

                int r = color.x * _factor;
                int g = color.y * _factor;
                int b = color.z * _factor;

                float rf = r / _factor;
                float gf = g / _factor;
                float bf = b / _factor;

                half4 color2 = half4(rf, gf, bf, 1.0);

                return color2;
            }
            
            ENDHLSL
        }
    }
}
