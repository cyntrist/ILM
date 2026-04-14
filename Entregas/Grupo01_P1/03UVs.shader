Shader "Custom/02Normales"
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

            // input vertex VS
            struct Attributes
            {
                float4 positionOS : POSITION;
                float2 uv : TEXCOORD0; // coordenadas de textura

                float3 normal : NORMAL;
            };

            // input fragment FS
            struct Varyings
            {
                float4 positionHCS : SV_POSITION;
                float2 uv : TEXCOORD0;

                float4 color : COLOR;
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
                OUT.positionHCS = TransformObjectToHClip(IN.positionOS.xyz);
                OUT.uv = TRANSFORM_TEX(IN.uv, _BaseMap);

                OUT.color.r = IN.uv.x;
                OUT.color.g = IN.uv.y;
                OUT.color.b = 0;
                OUT.color.a = 1.0;

                return OUT;
            }

            // FS / PS
            half4 frag(Varyings IN) : SV_Target
            {
                half4 color = IN.color;
                return color;
            }
            ENDHLSL
        }
    }
}
