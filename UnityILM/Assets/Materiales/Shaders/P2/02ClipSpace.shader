Shader "Custom/02ClipSpace"
{
    Properties
    {
        [MainColor] _BaseColor("Base Color", Color) = (1, 1, 1, 1)
        [MainTexture] _BaseMap("Base Map", 2D) = "white" {}
    }

    SubShader
    {
        Tags { "RenderType" = "Opaque" "RenderPipeline" = "UniversalPipeline" }

        Pass
        {
            HLSLPROGRAM

            #pragma vertex vert
            #pragma fragment frag

            #include "Packages/com.unity.render-pipelines.universal/ShaderLibrary/Core.hlsl"

            // VS
            struct Attributes
            {
                float4 positionOS : POSITION;
            };

            // PS
            struct Varyings
            {
                float4 pos : SV_POSITION;
                float4 pos2 : TEXCOORD0;
            };

            TEXTURE2D(_BaseMap);
            SAMPLER(sampler_BaseMap);

            CBUFFER_START(UnityPerMaterial)
                half4 _BaseColor;
                float4 _BaseMap_ST;
            CBUFFER_END

            // VS
            Varyings vert(Attributes IN)
            {
                Varyings OUT;

                OUT.pos = OUT.pos2 = TransformObjectToHClip(IN.positionOS.xyz);

                return OUT;
            }

            // PS
            half4 frag(Varyings IN) : SV_Target
            {
                return float4(abs(IN.pos2.xy / IN.pos2.w), 0.0f, 1.0f);
            }
            ENDHLSL
        }
    }
}

