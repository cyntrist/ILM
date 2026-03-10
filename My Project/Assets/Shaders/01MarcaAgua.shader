Shader "Custom/01MarcaAgua"
{
    Properties
    {
        [MainColor] _BaseColor("Base Color", Color) = (1, 1, 1, 1)
        [MainTexture] _BaseMap("Base Map", 2D) = "white" {}
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
            TEXTURE2D(_BaseMap);
            SAMPLER(sampler_BaseMap);

            CBUFFER_START(UnityPerMaterial)
                half4 _BaseColor;
                float4 _BaseMap_ST;
            CBUFFER_END

            half4 frag(Varyings input) : SV_Target
            {
                return SAMPLE_TEXTURE2D_X(_BlitTexture, sampler_BlitTexture, input.texcoord);
            }
            ENDHLSL
        }
    }
}
