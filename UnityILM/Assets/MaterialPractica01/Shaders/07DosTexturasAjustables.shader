Shader "Custom/04Textura"
{
    Properties
    {
        [MainColor] _BaseColor("Base Color", Color) = (1, 1, 1, 1)
    	
        [MainTexture] _MainTex ("Base (RGB)", 2D) = "" {}
        [SecondaryTexture] _SecondaryTex ("Secondary (RGB)", 2D) = "" {}
        [BlendTexture] _BlendTex ("Alpha Blended (___A)", 2D) = "" {}
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

            struct Attributes
            {
                float4 positionOS : POSITION;
                float2 uv : TEXCOORD0;

                float2 uv2 : TEXCOORD0;

                float2 uv3 : TEXCOORD0;

            };

            struct Varyings
            {
                float4 positionHCS : SV_POSITION;
                float2 uv : TEXCOORD0;

                float2 uv2 : TEXCOORD0;

                float2 uv3 : TEXCOORD0;
            };

            TEXTURE2D(_MainTex);
            SAMPLER(sampler_MainTex);

            TEXTURE2D(_SecondaryTex);
            SAMPLER(sampler_SecondaryTex);

            TEXTURE2D(_BlendTex);
            SAMPLER(sampler_BlendTex);

            CBUFFER_START(UnityPerMaterial)
                half4 _BaseColor;
                float4 _MainTex_ST;
                float4 _SecondaryTex_ST;
                float4 _BlendTex_ST;
            CBUFFER_END

            Varyings vert(Attributes IN)
            {
                Varyings OUT;
                OUT.positionHCS = TransformObjectToHClip(IN.positionOS.xyz);

                OUT.uv = TRANSFORM_TEX(IN.uv, _MainTex);

                OUT.uv2 = TRANSFORM_TEX(IN.uv2, _SecondaryTex);

                return OUT;
            }

            half4 frag(Varyings IN) : SV_Target
            {
                half4 color = (SAMPLE_TEXTURE2D(_MainTex, sampler_MainTex, IN.uv) + 
                SAMPLE_TEXTURE2D(_SecondaryTex, sampler_SecondaryTex, IN.uv2)) / 2;

                return color;
            }
            ENDHLSL
        }
    }
}
